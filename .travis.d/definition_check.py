import os
import sys
import re
import fnmatch

CURR_DIR = os.path.dirname(os.path.realpath(__file__))
DEF_FILE_PATH = os.path.join(CURR_DIR, '..', 'docs', 'definitions.dox')
INCLUDE_DIR = os.path.join(CURR_DIR, '..', 'include')

DEFINE_RULE = re.compile(r' \*     \\defgroup ([a-zA-Z]+) [a-zA-Z ]+')
USER_GROUP_RULE = re.compile(r' \* \\(user|kernel)group\{([a-zA-Z]+)\}')
IGNORE_FILES = [
    'vitasdk.h',
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

def check_headers(definitions):
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
                    errors.append('Has multiple groups: %s' % header_file)
                    break
                group = m.group(2)
                if definitions.get(group) == None:
                    errors.append('Unknown group: %s' % m.group(2))
                    break
                definitions[group] += 1
                have_group_define = True
            if not have_group_define:
                errors.append('Could not find definition: %s' % header_file)
    # reverse check if exist header
    for k, v in definitions.iteritems():
        if v == 0:
            errors.append('Could not find using header: %s' % k)
    return errors

if __name__ == '__main__':
    errors = check_headers(read_def_groups())
    if len(errors):
        for e in errors:
            print e
        sys.exit(1)
