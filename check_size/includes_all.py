#!/usr/bin/env python3
import sys
import re
import glob
import os

include_directive = re.compile(r"#include <([\w/]+\.h)>")
common_external_headers = frozenset(["stddef.h", "stdint.h", "stdarg.h"])
user_external_headers = common_external_headers.union(["time.h"])
kernel_external_headers = common_external_headers
all_external_headers = user_external_headers.union(kernel_external_headers)

def header_reach(root, include_dir = ""):
    if root in all_external_headers:
        return {root}

    root_path = os.path.join(include_dir, root)

    header = ""
    with open(root_path) as f:
        header = f.read()

    reach = {root}
    for include in include_directive.finditer(header):
        reach.update(header_reach(include.group(1), include_dir))

    return reach

def globs(gs, *, recursive=False, root_dir=None):
    return set().union(*(glob.glob(g, recursive=recursive, root_dir=root_dir) for g in gs))

def assert_reach(root_name, got, expected, possible=set()):
    unexpected_reach = got.difference(expected).difference(possible)
    if len(unexpected_reach) != 0:
        raise RuntimeError(f"{root_name} reaches unexpected files: {unexpected_reach}")

    unexpected_unreach = expected.difference(got)
    if len(unexpected_unreach) != 0:
        raise RuntimeError(f"{root_name} doesn't reach expected files: {unexpected_unreach}")

if __name__ == "__main__":
    include_dir = sys.argv[1]

    vitasdk_got = header_reach("vitasdk.h", include_dir)
    vitasdk = globs(["vitasdk.h", "vitasdk/build_utils.h", "vitasdk/utils.h", "psp2/**/*.h"], recursive=True, root_dir=include_dir).union(user_external_headers)
    psp2_common = glob.glob("psp2common/**/*.h", recursive=True, root_dir=include_dir)
    assert_reach("`vitasdk.h`", vitasdk_got, vitasdk, psp2_common)

    vitasdkkern_got = header_reach("vitasdkkern.h", include_dir)
    vitasdkkern = globs(["vitasdkkern.h", "vitasdk/build_utils.h", "psp2kern/**/*.h"], recursive=True, root_dir=include_dir).union(kernel_external_headers)
    assert_reach("`vitasdkkern.h`", vitasdkkern_got, vitasdkkern, psp2_common)

    vitasdkall_got = vitasdk_got.union(vitasdkkern_got)
    vitasdkall = set(glob.glob("**/*.h", recursive=True, root_dir=include_dir)).union(all_external_headers)
    assert_reach("`vitasdk.h` or `vitasdkkern.h`", vitasdkall_got, vitasdkall)
