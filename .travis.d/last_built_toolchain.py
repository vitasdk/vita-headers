import re
import json
import urllib2

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

def find_sdk(page):
    for line in page.split('\n'):
        if 'linux' not in line or 'tar.bz2' not in line:
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
                #print build
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

for tag in fetch_succeeded_tags():
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
