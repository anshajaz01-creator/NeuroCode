"""
Turn raw Project CodeNet submissions into clean, labeled C++ snippets.

Supports two layouts:

  full      Project_CodeNet/data/pXXXXX/C++/sXXXXXXXXX.cpp
            Project_CodeNet/metadata/pXXXXX.csv      (has a 'status' column)

  benchmark Project_CodeNet_C++1000/pXXXXX/sXXXXXXXXX.cpp
            (already filtered to accepted submissions, no metadata csv)

What it does per submission:
  1. keep only C++ and, where metadata exists, only status == Accepted
  2. strip includes, macros, using-directives, and the competitive-programming
     I/O boilerplate that would otherwise dominate the feature vector
  3. wrap what is left in a compilable unit
  4. g++ -fsyntax-only, discard anything that does not compile
  5. write to data/prepared/<label>/<problem>_<submission>.cpp

Usage:
  python3 codenet_prepare.py --root /path/to/CodeNet --layout benchmark \
      --map data/problem_map.json --out data/prepared --limit 200
"""
import argparse
import csv
import json
import pathlib
import re
import subprocess
import tempfile

# Matches an I/O statement ANYWHERE in the line, so that one-liner input loops
# such as `for(int i=0;i<n;i++) cin>>a[i];` are removed whole. Those loops are
# the single biggest source of feature noise in competitive submissions.
IO_LINE = re.compile(
    r"(cin\s*>>|cout\s*<<|cerr\s*<<|scanf\s*\(|printf\s*\(|puts\s*\(|"
    r"ios_base::sync_with_stdio|ios::sync_with_stdio|cin\.tie|cout\.tie|"
    r"freopen\s*\(|getline\s*\()"
)
# Only includes are dropped. #define and using-directives are KEPT: competitive
# code leans on macros like `#define int long long` and `#define rep(i,n) ...`,
# and removing them leaves code that cannot compile.
DROP_LINE = re.compile(r"^\s*#\s*include")

PREAMBLE = """#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <bitset>
#include <list>
#include <climits>
#include <cmath>
#include <cstring>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
"""


def strip_io(src: str) -> str:
    """Remove boilerplate lines. Deliberately line-based and crude: a real
    AST rewrite is not worth the time, and the failures are caught by the
    compile gate downstream."""
    out = []
    for line in src.splitlines():
        if DROP_LINE.match(line):
            continue
        if IO_LINE.match(line):
            continue
        out.append(line)
    text = "\n".join(out)
    # `signed main` is the idiom that pairs with `#define int long long`.
    # Rewriting it to `int main` there expands to `long long main`, which is
    # a hard error. Only rewrite when that macro is absent.
    if not re.search(r"#\s*define\s+int\s+long\s+long", text):
        text = text.replace("signed main", "int main")
    return text


def compiles(src: str) -> bool:
    with tempfile.NamedTemporaryFile("w", suffix=".cpp", delete=False) as f:
        f.write(src)
        path = f.name
    try:
        r = subprocess.run(
            ["g++", "-std=c++17", "-fsyntax-only", "-w", path],
            capture_output=True, timeout=20,
        )
        return r.returncode == 0
    except subprocess.TimeoutExpired:
        return False
    finally:
        pathlib.Path(path).unlink(missing_ok=True)


def accepted_ids(meta_csv: pathlib.Path):
    """Submission ids with status Accepted and language C++."""
    keep = set()
    with open(meta_csv, newline="", encoding="utf-8", errors="ignore") as f:
        for row in csv.DictReader(f):
            lang = (row.get("language") or "").strip()
            status = (row.get("status") or "").strip()
            if lang.startswith("C++") and status == "Accepted":
                keep.add(row.get("submission_id", "").strip())
    return keep


def iter_submissions(root: pathlib.Path, layout: str, problem: str):
    if layout == "benchmark":
        d = root / problem
        if not d.is_dir():
            return
        for f in sorted(d.glob("*.cpp")):
            yield f
    else:
        d = root / "data" / problem / "C++"
        meta = root / "metadata" / f"{problem}.csv"
        keep = accepted_ids(meta) if meta.exists() else None
        if not d.is_dir():
            return
        for f in sorted(d.glob("*.cpp")):
            if keep is not None and f.stem not in keep:
                continue
            yield f


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", required=True)
    ap.add_argument("--layout", choices=["full", "benchmark"], default="benchmark")
    ap.add_argument("--map", required=True, help="problem_map.json")
    ap.add_argument("--out", default="data/prepared")
    ap.add_argument("--limit", type=int, default=200, help="max kept per problem")
    args = ap.parse_args()

    root = pathlib.Path(args.root)
    pmap = json.load(open(args.map))["problems"]
    out_root = pathlib.Path(args.out)

    stats = {}
    for problem, info in pmap.items():
        label = info["label"]
        kept = seen = 0
        dest = out_root / label
        dest.mkdir(parents=True, exist_ok=True)
        for f in iter_submissions(root, args.layout, problem):
            seen += 1
            if kept >= args.limit:
                break
            raw = f.read_text(errors="ignore")
            if len(raw) > 20000:
                continue
            body = PREAMBLE + strip_io(raw)
            if not compiles(body):
                continue
            (dest / f"{problem}_{f.stem}.cpp").write_text(body)
            kept += 1
        stats[problem] = {"label": label, "seen": seen, "kept": kept}
        print(f"{problem:10s} {label:26s} seen={seen:5d} kept={kept:5d}")

    json.dump(stats, open(out_root / "_prepare_stats.json", "w"), indent=2)
    total = sum(s["kept"] for s in stats.values())
    print(f"\ntotal kept: {total}")


if __name__ == "__main__":
    main()
