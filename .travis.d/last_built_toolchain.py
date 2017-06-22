import re
import json
import urllib

TRAVIS_REPO_ID = '10768510'
GITHUB_REPO = 'vitasdk/autobuilds'

TRAVIS_API = 'https://api.travis-ci.org/repos/' + TRAVIS_REPO_ID
GITHUB = 'https://github.com'
GITHUB_REL = GITHUB + '/' + GITHUB_REPO + '/releases'
GITHUB_TAG = GITHUB_REL + '/tag'
TAG_FORMAT = '%(branch)s-%(os)s-v%(build)s'
REGEX = re.compile('href="([^"]*)"')

def find_sdk(page):
    for line in page.split('\n'):
        if 'linux' not in line or 'tar.bz2' not in line:
            continue
        m = REGEX.search(line)
        if not m:
            continue
        return m.group(1)

build_info = json.load(urllib.urlopen(TRAVIS_API))
number = build_info['last_build_number']
# just check last 10 build
for x in range(10):
    tag = (TAG_FORMAT % dict(branch='master', os='linux', build=int(number) - x))
    path = find_sdk(urllib.urlopen(GITHUB_TAG + '/' + tag).read())
    if not path:
        continue
    print GITHUB + path
    raise SystemExit(0)

raise SystemExit(1)
