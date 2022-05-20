import re
import json
try:
    import urllib2
except ImportError:
    # python3?
    import urllib.request as urllib2

GITHUB_REPO = 'vitasdk/autobuilds'
GITHUB_API = 'https://api.github.com'
GITHUB_REL = GITHUB_API + '/repos/' + GITHUB_REPO + '/releases'

def fetch_last_release(branch='master', os='linux'):
    req = urllib2.Request(GITHUB_REL)
    builds = json.load(urllib2.urlopen(req))

    for build in builds:
        if not build['assets'] or not build['assets'][0]['browser_download_url']:
            continue
        if build['target_commitish'] != branch:
            continue
        if os not in build['tag_name']:
            continue

        return build['assets'][0]['browser_download_url']

if __name__ == '__main__':
    import sys

    url = fetch_last_release(*sys.argv[1:])
    if not url:
        raise SystemExit(1)
    print(url)
    raise SystemExit(0)
