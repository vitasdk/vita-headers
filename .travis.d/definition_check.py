import os
import sys
import re
import glob
import fnmatch

CURR_DIR = os.path.dirname(os.path.realpath(__file__))
DEF_FILE = 'definitions.dox'
DEF_FILE_PATH = os.path.join(CURR_DIR, '..', 'docs', DEF_FILE)
DB_FILE_PATH = os.path.join(CURR_DIR, '..', 'db', '360', '*.yml')
INCLUDE_DIR = os.path.join(CURR_DIR, '..', 'include')

DEFINE_RULE = re.compile(r' \*     \\defgroup (Sce\w+) \w+')
USER_GROUP_RULE = re.compile(r' \* \\(user|kernel)group\{(Sce\w+)\}')

FUNC_RULE_PATTERN = (
    # ret
    r'^\s*(?!(?:return|typedef)\b)(?:[A-Za-z_]\w*\s+)*[A-Za-z_]\w*' +
    r'(?:\s*\*+\s*|\s+)' +
    # func name
    r'(_*k?sce\w+|__\w+)' +
    # args; if define with multiline, end with comma, if not end with `);`
    r'\(.*(?:,|\);)' +
    # white spaces
    r'\s*$'
)
FUNCTION_RULE = re.compile(FUNC_RULE_PATTERN)
IGNORE_FILES = [
    'vitasdk.h',
    'vitasdkkern.h',
    'vitasdk/utils.h',
    'vitasdk/build_utils.h',
]

# older python's glob not support `**`
def findfile(directory, filepattern):
    matches = []
    for root, dirnames, filenames in os.walk(directory):
        for filename in fnmatch.filter(filenames, filepattern):
            matches.append(os.path.join(root, filename))
    return matches

def readlines(f):
    if sys.version_info.major < 3:
        return f.xreadlines()
    return f

def dict_items(dic):
    if sys.version_info.major < 3:
        return dic.iteritems()
    return dic.items()

def function_nid_aliases(domain, fn):
    aliases = [fn]
    if domain == 'psp2':
        if fn.startswith('_sce'):
            aliases.append(fn[1:])
        elif fn.startswith('sce'):
            aliases.append('_' + fn)
    elif domain == 'psp2kern':
        if fn.startswith('ksce'):
            aliases.append(fn[1:])
        elif fn.startswith('sce'):
            aliases.append('k' + fn)
    return aliases

def read_def_groups():
    definitions = dict()
    with open(DEF_FILE_PATH, 'r') as d:
        for line in readlines(d):
            m = DEFINE_RULE.match(line)
            if not m:
                continue
            definitions[m.group(1)] = 0
    return definitions

def read_nids():
    errors = []
    user_nids = dict()
    kernel_nids = dict()
    nids = None
    for fn in glob.glob(DB_FILE_PATH):
        with open(fn, 'r') as d:
            SECTION = None
            for line_no, line in enumerate(readlines(d)):
                line = line.strip()
                k, v = line.split(':')[:3]
                if k[0] == "#": # It a comment
                    continue
                if not v.strip():
                    SECTION = k
                    continue
                if k.strip() == 'kernel':
                    if v.strip() == 'true':
                        nids = kernel_nids
                    else:
                        nids = user_nids
                if SECTION != 'functions':
                    continue
                # Same name is now handled by vita-nid-check
                # if nids.get(k):
                #     errors.append('%s: NID conflict %s' % (line_no + 1, k))
                nids[k] = 1
    return {
        'psp2': user_nids,
        'psp2kern': kernel_nids,
    }, errors

def check_header_groups(definitions):
    errors = []
    # check exists in definitions
    for header_path in findfile(INCLUDE_DIR, '*.h'):
        header_file = header_path.split('include/')[1]
        if header_file in IGNORE_FILES:
            continue
        with open(header_path, 'r') as h:
            have_group_define = False
            for line in readlines(h):
                m = USER_GROUP_RULE.match(line)
                if not m:
                    continue
                if have_group_define:
                    errors.append('%s: Has multiple groups' % header_file)
                    break
                group = m.group(2)
                if definitions.get(group) == None:
                    errors.append('%s: Unknown group %s' %
                                  (header_file, m.group(2)))
                    break
                definitions[group] += 1
                have_group_define = True
            if not have_group_define:
                errors.append('%s: Could not find definition' % header_file)
    # reverse check if exist header
    for k, v in dict_items(definitions):
        if v == 0:
            errors.append('%s: Could not find using header: %s' %
                          (DEF_FILE, k))
    return errors

def check_function_nids(nids_by_domain):
    errors = []
    functions = dict()
    for header_path in findfile(INCLUDE_DIR, '*.h'):
        header_file = header_path.split('include/')[1]
        domain = header_file.split('/', 1)[0]
        if header_file in IGNORE_FILES:
            continue
        with open(header_path, 'r') as h:
            have_group_define = False
            for line in readlines(h):
                m = FUNCTION_RULE.match(line)
                if not m:
                    continue
                fn = m.group(1)
                function_key = (domain, fn)
                if functions.get(function_key):
                    errors.append('%s: Already defined %s' %
                                  (header_file, fn))
                    continue
                domain_nids = nids_by_domain.get(domain)
                have_nid = domain_nids is None or any(
                    domain_nids.get(alias)
                    for alias in function_nid_aliases(domain, fn)
                )
                if not have_nid:
                    errors.append('%s: Could not find NID %s' %
                                  (header_file, fn))
                functions[function_key] = 1
    return errors

if __name__ == '__main__':
    nids, errors = read_nids()
    errors += check_header_groups(read_def_groups()) \
        + check_function_nids(nids)
    if len(errors):
        for e in errors:
            print(e)
        sys.exit(1)
