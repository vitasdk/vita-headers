import re
import json
import urllib2

TRAVIS_REPO_ID = '10768510'
GITHUB_REPO = 'vitasdk/autobuilds'

TRAVIS_API = 'https://api.travis-ci.org/repos/' + TRAVIS_REPO_ID
GITHUB = 'https://github.com'
GITHUB_REL = GITHUB + '/' + GITHUB_REPO + '/releases'
GITHUB_TAG = GITHUB_REL + '/tag'
TAG_FORMAT = '%(branch)s-%(os)s-v%(build)s'
REGEX = re.compile('href="([^"]*)"')
HEADERS = dict(Accept='application/vnd.travis-ci.2+json')

def find_sdk(page):
    for line in page.split('\n'):
        if 'linux' not in line or 'tar.bz2' not in line:
            continue
        m = REGEX.search(line)
        if not m:
            continue
        return m.group(1)

req = urllib2.Request(TRAVIS_API, headers=HEADERS)
build_info = json.load(urllib2.urlopen(req))
number = build_info['repo']['last_build_number']
# just check last 25 builds
for x in range(25):
    tag = (TAG_FORMAT % dict(branch='master', os='linux', build=int(number) - x))
    req = urllib2.Request(GITHUB_TAG + '/' + tag)
    try:
        path = find_sdk(urllib2.urlopen(req).read())
        if not path:
            continue
    except urllib2.HTTPError:
        continue
    print GITHUB + path
    raise SystemExit(0)

raise SystemExit(1)
