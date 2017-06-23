import os
import sys
import re
import fnmatch

CURR_DIR = os.path.dirname(os.path.realpath(__file__))
DEF_FILE = 'definitions.dox'
DEF_FILE_PATH = os.path.join(CURR_DIR, '..', 'docs', DEF_FILE)
DB_FILE = 'db.yml'
DB_FILE_PATH = os.path.join(CURR_DIR, '..', 'db.yml')
INCLUDE_DIR = os.path.join(CURR_DIR, '..', 'include')

DEFINE_RULE = re.compile(r' \*     \\defgroup (Sce\w+) \w+')
USER_GROUP_RULE = re.compile(r' \* \\(user|kernel)group\{(Sce\w+)\}')

FUNC_RULE_PATTERN = (
    # ret
    '^\w+\s+' +
    # func name
    '(_*k?sce\w+|__\w+)' +
    # args; if define with multiline, end with comma, if not end with `);`
    '\(.*(,|\);)' +
    # white spaces
    '\s*$'
)
FUNCTION_RULE = re.compile(FUNC_RULE_PATTERN)
IGNORE_FILES = [
    'vitasdk.h',
    'vitasdkkern.h',
    'vitasdk/utils.h',
]

# older python's glob not support `**`
def findfile(directory, filepattern):
    matches = []
    for root, dirnames, filenames in os.walk(directory):
        for filename in fnmatch.filter(filenames, filepattern):
            matches.append(os.path.join(root, filename))
    return matches

def read_def_groups():
    definitions = dict()
    with open(DEF_FILE_PATH, 'r') as d:
        for line in d.xreadlines():
            m = DEFINE_RULE.match(line)
            if not m:
                continue
            definitions[m.group(1)] = 0
    return definitions

def read_nids():
    nids = dict()
    with open(DB_FILE_PATH, 'r') as d:
        SECTION = None
        for line in d.xreadlines():
            line = line.strip()
            k, v = line.split(':')[:2]
            if not v.strip():
                SECTION = k
                continue
            if SECTION != 'functions':
                continue
            nids[k] = 1
    return nids

def check_header_groups(definitions):
    errors = []
    # check exists in definitions
    for header_path in findfile(INCLUDE_DIR, '*.h'):
        header_file = header_path.split('include/')[1]
        if header_file in IGNORE_FILES:
            continue
        with open(header_path, 'r') as h:
            have_group_define = False
            for line in h.xreadlines():
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
    for k, v in definitions.iteritems():
        if v == 0:
            errors.append('%s: Could not find using header: %s' %
                          (DEF_FILE, k))
    return errors

def check_function_nids(nids):
    errors = []
    functions = dict()
    for header_path in findfile(INCLUDE_DIR, '*.h'):
        header_file = header_path.split('include/')[1]
        if header_file in IGNORE_FILES:
            continue
        with open(header_path, 'r') as h:
            have_group_define = False
            for line in h.xreadlines():
                m = FUNCTION_RULE.match(line)
                if not m:
                    continue
                fn = m.group(1)
                if functions.get(fn):
                    errors.append('%s: Already defined %s' %
                                  (header_file, fn))
                    continue
                if not nids.get(fn):
                    errors.append('%s: Could not find NID %s' %
                                  (header_file, fn))
                functions[fn] = 1
    return errors

if __name__ == '__main__':
    errors = check_header_groups(read_def_groups()) \
        + check_function_nids(read_nids())
    if len(errors):
        for e in errors:
            print e
        sys.exit(1)
