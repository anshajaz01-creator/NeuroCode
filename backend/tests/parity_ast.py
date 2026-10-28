#!/usr/bin/env python3
"""Parity check between T1's Python extractor and the C++ AST builder.

For every sample .cpp, this runs
  1. nc_extract           (C++)    -> AST JSON
  2. tools/extract_ast.py (Python) -> AST JSON, on the SAME text (preamble + #line + code)
and compares the two trees node for node, then runs tools/features.py on both and compares the
feature vectors. A difference in either means the model would see different input in production
than it trained on.

Known, deliberate differences (see parse/AstBuilder.hpp) are normalised away before comparing:
  - "line": Python reports lines in the file it parsed, C++ reports lines in the user's code
  - the root "spelling"
  - the preamble's `using namespace std;` child of the root

Run from backend/:
  python3 tests/parity_ast.py --nc-extract build/nc_extract [--tools tools] [--samples tests/fixtures/ast_samples]
Set NC_LIBCLANG=/path/to/libclang.so to make the Python side use the same libclang as the C++ side;
two different libclang versions can legitimately disagree on dtype spellings.
"""
import argparse, glob, json, os, subprocess, sys, tempfile


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--nc-extract", required=True)
    ap.add_argument("--tools", default="tools")
    ap.add_argument("--samples", default="tests/fixtures/ast_samples")
    ap.add_argument("--show", type=int, default=5, help="max differences to print per file")
    args = ap.parse_args()

    sys.path.insert(0, args.tools)
    import clang.cindex as ci
    if os.environ.get("NC_LIBCLANG"):
        ci.Config.set_library_file(os.environ["NC_LIBCLANG"])
    import extract_ast, features

    files = sorted(glob.glob(os.path.join(args.samples, "*.cpp")))
    if not files:
        sys.exit(f"no samples in {args.samples}")

    bad = 0
    for path in files:
        name = os.path.basename(path)
        wrapped = subprocess.run([args.nc_extract, "--print-wrapped", path], capture_output=True, text=True, check=True).stdout
        delta = wrapped.split("\n").index('#line 1 "user.cpp"') + 1      # real line of the #line directive

        with tempfile.NamedTemporaryFile("w", suffix=".cpp", delete=False) as f:
            f.write(wrapped)
            tmp = f.name
        try:
            py_ast, _ = extract_ast.parse_file(tmp)
        finally:
            os.unlink(tmp)
        out = subprocess.run([args.nc_extract, path], capture_output=True, text=True)
        if out.returncode != 0:
            print(f"FAIL {name}: nc_extract exited {out.returncode}: {out.stderr.strip()[:200]}")
            bad += 1
            continue
        cpp_ast = json.loads(out.stdout)

        # normalise the deliberate differences
        py_ast["children"] = [c for c in py_ast["children"] if c["line"] > delta]
        def fix(n):
            if n["line"] > 0:
                n["line"] -= delta
            for c in n["children"]:
                fix(c)
        fix(py_ast)
        py_ast["spelling"] = cpp_ast["spelling"] = ""

        diffs = []
        def cmp(a, b, path_):
            for key in sorted(set(a) | set(b)):
                if key == "children":
                    continue
                if a.get(key, "<absent>") != b.get(key, "<absent>"):
                    diffs.append(f"{path_} {a['type']}.{key}: python={a.get(key,'<absent>')!r} c++={b.get(key,'<absent>')!r}")
            if len(a["children"]) != len(b["children"]):
                diffs.append(f"{path_} {a['type']}: python has {len(a['children'])} children, c++ has {len(b['children'])}")
                return
            for i, (x, y) in enumerate(zip(a["children"], b["children"])):
                cmp(x, y, f"{path_}/{i}")
        cmp(py_ast, cpp_ast, "")

        v_py, v_cpp = features.extract(py_ast), features.extract(cpp_ast)
        feat_diffs = [(features.FEATURE_NAMES[i], a, b) for i, (a, b) in enumerate(zip(v_py, v_cpp)) if a != b]

        if diffs or feat_diffs:
            bad += 1
            print(f"FAIL {name}: {len(diffs)} tree differences, {len(feat_diffs)} feature differences")
            for d in diffs[:args.show]:
                print("   ", d)
            for n, a, b in feat_diffs[:args.show]:
                print(f"    feature {n}: python={a} c++={b}")
        else:
            nodes = sum(1 for _ in features._walk(cpp_ast))
            print(f"ok   {name}: {nodes} nodes identical, {len(v_py)} features identical")

    print("ALL IDENTICAL" if not bad else f"{bad} of {len(files)} files differ")
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
