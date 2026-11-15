import re
import json
import os
import platform
import sys
try:
    import urllib2
except ImportError:
    # python3?
    import urllib.request as urllib2

GITHUB_REPO = 'vitasdk/autobuilds'
GITHUB_API = 'https://api.github.com'
GITHUB_REL = GITHUB_API + '/repos/' + GITHUB_REPO + '/releases?per_page=100'

try:
    token = os.environ['TOKEN']
except KeyError:
    token = None

def get_host_triplet(os_name):
    architecture = platform.machine().lower()
    if architecture in ('amd64', 'x86-64'):
        architecture = 'x86_64'
    elif architecture == 'arm64' and os_name == 'linux':
        architecture = 'aarch64'

    if os_name == 'linux':
        return architecture + '-linux-gnu'
    if os_name == 'osx':
        return architecture + '-apple-darwin'
    if os_name == 'win':
        return architecture + '-w64-mingw32'

    # Also accept a complete triplet for newer callers.
    return os_name


def fetch_last_release(branch='master', os='linux', page=1):
    triplet = get_host_triplet(os)
    asset_pattern = re.compile(
        r'^vitasdk-' + re.escape(triplet) + r'-.+\.tar\.bz2$'
    )
    req = urllib2.Request(GITHUB_REL+'&page=' + str(page))
    if token:
        req.add_header('Authorization', 'Bearer ' + token);
    try:
        builds = json.load(urllib2.urlopen(req))

        for build in builds:
            if build['target_commitish'] != branch:
                continue

            for asset in build.get('assets', []):
                if asset_pattern.match(asset.get('name', '')):
                    return asset.get('browser_download_url')
    except urllib2.HTTPError as e:
        sys.stderr.write(str(e) + "\n")
        sys.stderr.write(str(e.headers) + "\n")
        return None

if __name__ == '__main__':
    import sys

    for page in range(1,6):
        url = fetch_last_release(*sys.argv[1:3], page=page)
        if not url:
            continue
        break

    if not url:
        raise SystemExit(1)
    print(url)
    raise SystemExit(0)
