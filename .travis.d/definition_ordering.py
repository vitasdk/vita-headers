import os
import sys
import re
import fnmatch

CURR_DIR = os.path.dirname(os.path.realpath(__file__))
DB_FILE = 'db.yml'
DB_FILE_PATH = os.path.join(CURR_DIR, '..', 'db.yml')
SECTIONS = ('functions', 'variables')

def read_nid_groups():
    groups = []
    with open(DB_FILE_PATH, 'r') as d:
        SECTION = None
        lines = None
        for line in d.xreadlines():
            line = line.strip()
            k, v = line.split(':')[:4]
            if not v.strip():
                SECTION = k
                if SECTION in SECTIONS:
                    lines = []
                    groups.append(lines)
                continue
            if SECTION in SECTIONS:
                lines.append(line)
    return groups

def check_nids(groups):
    errors = []
    for lines in groups:
        ps = ['']
        for idx, line in enumerate(lines):
            p = ps[-1]
            if cmp(p.split(':')[0], line.split(':')[0]) <= 0:
                ps.append(line)
                continue
            errors.append('disorder: %s' % p.split(':')[0].strip())
            ps.pop()
    return errors

if __name__ == '__main__':
    errors = check_nids(read_nid_groups())
    if len(errors):
        for e in errors:
            print e
        sys.exit(1)
