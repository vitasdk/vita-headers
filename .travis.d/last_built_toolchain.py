import re
import json
try:
    import urllib2
except ImportError:
    # python3?
    import urllib.request as urllib2

TRAVIS_REPO_ID = 10768510
GITHUB_REPO = 'vitasdk/autobuilds'
TRAVIS_API = 'https://api.travis-ci.org'
TRAVIS_BUILDS = TRAVIS_API + '/repo/%d/builds' % TRAVIS_REPO_ID
GITHUB = 'https://github.com'
GITHUB_REL = GITHUB + '/' + GITHUB_REPO + '/releases'
GITHUB_TAG = GITHUB_REL + '/tag'
TAG_FORMAT = '%(branch)s-%(os)s-v%(build)s'
REGEX = re.compile('href="([^"]*)"')
HEADERS = dict()
HEADERS['Travis-API-Version'] = 3

def find_sdk(page, os='linux'):
    for line in page.decode('utf-8').split('\n'):
        if os not in line or 'tar.bz2' not in line:
            continue
        m = REGEX.search(line)
        if not m:
            continue
        return m.group(1)

def pager(page, limit=20):
    return 'limit=%(limit)d&offset=%(offset)d' % dict(limit=limit, offset=page * limit)

def fetch_succeeded_tags(branch='master', os='linux'):
    for page in range(5):
        try:
            build_url = ''.join((
                TRAVIS_BUILDS, '?',
                pager(page),
                '&branch=' + branch,
                '&include=job.config,job.state',
            ))
            req = urllib2.Request(build_url, headers=HEADERS)
            builds = json.load(urllib2.urlopen(req))

            for build in builds['builds']:
                for job in build['jobs']:
                    if job['state'] != 'passed':
                        continue
                    # windows build
                    if 'TOXENV=WIN' in job['config'].get('env', ''):
                        if os != 'win':
                            continue
                    elif job['config']['os'] != os:
                        continue

                    yield (TAG_FORMAT % dict(branch=branch,
                                             os=os,
                                             build=build['number']))
        except urllib2.HTTPError:
            # FIXME: need to check; network error
            continue
        except ValueError:
            # FIXME: need to check; json parse error
            continue

def last_built_toolchain(branch='master', os='linux'):
    for tag in fetch_succeeded_tags(branch=branch, os=os):
        req = urllib2.Request(GITHUB_TAG + '/' + tag)
        try:
            path = find_sdk(urllib2.urlopen(req).read(), os=os)
            if not path:
                continue
        except urllib2.HTTPError:
            continue
        return GITHUB + path

if __name__ == '__main__':
    import sys

    url = last_built_toolchain(*sys.argv[1:])
    if not url:
        raise SystemExit(1)
    print(url)
    raise SystemExit(0)
