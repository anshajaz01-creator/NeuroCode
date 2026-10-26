#!/usr/bin/env python3
"""
Turn each hand-written seed into label-preserving variants.

Input : data/seeds/<label>/<nnn>.cpp
Output: data/mutated/<label>/<nnn>_mXX.cpp   (m00 = the original seed)
        data/manifest_seeds.csv              sample_id,label,source,group_id,path

Mutations (combined at random per variant):
  rename     consistent renaming of variables, parameters and function names
  for2while  rewrite a braced for-loop as an equivalent while-loop
  increment  i++  ->  ++i / i += 1 / i = i + 1
  dead       insert an unused declaration at the top of the function body

Every variant is compile-checked; variants that fail or duplicate another are dropped.
All variants of one seed share a group_id, so they always land in the same split.

Run from backend/:
  python3 tools/mutate_seeds.py              # ~20 variants per seed
  python3 tools/mutate_seeds.py --variants 5 # quick test
"""
import argparse, csv, glob, hashlib, os, random, re, subprocess, tempfile

KEYWORDS = set("""
alignas alignof and asm auto bool break case catch char class const constexpr const_cast continue
decltype default delete do double dynamic_cast else enum explicit extern false float for friend goto
if inline int long mutable namespace new noexcept not nullptr operator or private protected public
register reinterpret_cast return short signed sizeof static static_cast struct switch template this
throw true try typedef typeid typename union unsigned using virtual void volatile while
""".split())
LIBRARY = set("""
std vector string pair unordered_map unordered_set map set queue priority_queue stack deque greater less
sort max min abs swap lower_bound upper_bound max_element min_element accumulate begin end size
push_back pop_back push pop top front back insert erase count find empty first second size_t
INT_MAX INT_MIN LLONG_MAX LLONG_MIN main
""".split())
# Neutral names only. Names that hint at an algorithm (lo, hi, mid, left, right, dp, memo,
# seen, heap, window ...) and names that features.py reads (i, idx, p, mid) are excluded,
# so renaming never adds or fakes a clue.
NAME_POOL = """a b c d e f g h q r s t u v w x y z aa bb cc xx yy zz val arr nums data lst seq
res out tmp aux buf num elem item foo bar baz qux alpha beta gamma delta var1 var2 var3 obj
in1 in2 tmpv tval""".split()

TOKEN = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_]\w*|\s+|.', re.S)


def tokens(code):
    return TOKEN.findall(code)


def protected_names(toks):
    """Identifiers used as members (after . or ->) are never renamed anywhere."""
    prot = set()
    prev = []
    for t in toks:
        if t.strip() == "":
            continue
        if re.match(r'[A-Za-z_]\w*$', t) and prev and (prev[-1] == "." or prev[-2:] == ["-", ">"]):
            prot.add(t)
        prev.append(t)
    return prot


def mut_rename(code, rng):
    lines = code.split("\n")
    head = [l for l in lines if l.startswith("#") or l.startswith("using namespace")]
    body = "\n".join(l for l in lines if l not in head)
    toks = tokens(body)
    prot = protected_names(toks)
    idents = []
    for t in toks:
        if re.match(r'[A-Za-z_]\w*$', t) and t not in KEYWORDS and t not in LIBRARY \
                and t not in prot and t not in idents:
            idents.append(t)
    taken = set(KEYWORDS) | LIBRARY | prot
    pool = NAME_POOL[:]
    rng.shuffle(pool)
    mapping = {}
    for i, name in enumerate(idents):
        cand = pool[i] if i < len(pool) else f"v{i}"
        while cand in taken or cand in mapping.values():
            cand = cand + str(rng.randint(0, 9))
        mapping[name] = cand
    out = "".join(mapping.get(t, t) for t in toks)
    return "\n".join(head + [out]) if head else out


def _match(code, i, open_c, close_c):
    depth = 0
    for j in range(i, len(code)):
        if code[j] == open_c:
            depth += 1
        elif code[j] == close_c:
            depth -= 1
            if depth == 0:
                return j
    return -1


def _split_top(s, sep=";"):
    parts, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == sep and depth == 0:
            parts.append(cur); cur = ""
        else:
            cur += ch
    parts.append(cur)
    return parts


def mut_for2while(code, rng):
    cands = []
    for m in re.finditer(r'\bfor\s*\(', code):
        p_open = m.end() - 1
        p_close = _match(code, p_open, "(", ")")
        if p_close < 0:
            continue
        header = code[p_open + 1:p_close]
        parts = _split_top(header)
        if len(parts) != 3:
            continue  # range-for or unusual
        k = p_close + 1
        while k < len(code) and code[k].isspace():
            k += 1
        if k >= len(code) or code[k] != "{":
            continue
        b_close = _match(code, k, "{", "}")
        if b_close < 0:
            continue
        body = code[k + 1:b_close]
        if re.search(r'\bcontinue\b', body):
            continue
        cands.append((m.start(), b_close, parts, body))
    if not cands:
        return code
    start, end, (init, cond, inc), body = rng.choice(cands)
    init, cond, inc = init.strip(), cond.strip() or "true", inc.strip()
    inc_stmt = f" {inc};" if inc else ""
    repl = "{ " + (init + "; " if init else "") + f"while ({cond}) {{" + body.rstrip() + inc_stmt + " } }"
    return code[:start] + repl + code[end + 1:]


def mut_increment(code, rng):
    def sub(m):
        v = m.group(1)
        return rng.choice([f"++{v}", f"{v} += 1", f"{v} = {v} + 1", f"{v}++"])
    return re.sub(r'(?<![\w+])([A-Za-z_]\w*)\+\+(?=\s*\))', sub, code)


def mut_dead(code, rng):
    m = re.search(r'\)\s*(const\s*)?\{', code)
    if not m:
        return code
    n = rng.randint(1, 99)
    stmt = rng.choice([
        f" int unused_{n} = {n}; (void)unused_{n};",
        f" bool flag_{n} = false; (void)flag_{n};",
        f" long long pad_{n} = 0; (void)pad_{n};",
    ])
    return code[:m.end()] + stmt + code[m.end():]


MUTATIONS = [mut_rename, mut_for2while, mut_increment, mut_dead]


def compiles(code):
    with tempfile.NamedTemporaryFile("w", suffix=".cpp", delete=False) as f:
        f.write(code); path = f.name
    try:
        r = subprocess.run(["g++", "-std=c++17", "-fsyntax-only", path],
                           stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, timeout=20)
        return r.returncode == 0
    except subprocess.TimeoutExpired:
        return False
    finally:
        os.unlink(path)


def norm_hash(code):
    return hashlib.sha1(re.sub(r"\s+", " ", code).strip().encode()).hexdigest()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--seeds", default="data/seeds")
    ap.add_argument("--out-dir", default="data/mutated")
    ap.add_argument("--manifest", default="data/manifest_seeds.csv")
    ap.add_argument("--variants", type=int, default=20, help="variants per seed, including the original")
    ap.add_argument("--seed", type=int, default=42)
    args = ap.parse_args()
    rng = random.Random(args.seed)

    rows, per_label, failed = [], {}, 0
    for path in sorted(glob.glob(os.path.join(args.seeds, "*", "*.cpp"))):
        label = os.path.basename(os.path.dirname(path))
        stem = os.path.splitext(os.path.basename(path))[0]
        group = f"seed_{label}_{stem}"
        original = open(path).read()
        outdir = os.path.join(args.out_dir, label)
        os.makedirs(outdir, exist_ok=True)

        seen, variants, attempts = set(), [], 0
        variants.append(original); seen.add(norm_hash(original))
        while len(variants) < args.variants and attempts < args.variants * 6:
            attempts += 1
            code = original
            chosen = [m for m in MUTATIONS if rng.random() < 0.6] or [rng.choice(MUTATIONS)]
            for m in chosen:
                code = m(code, rng)
            h = norm_hash(code)
            if h in seen:
                continue
            if not compiles(code):
                failed += 1
                continue
            seen.add(h); variants.append(code)

        for i, code in enumerate(variants):
            sid = f"{group}_m{i:02d}"
            out = os.path.join(outdir, f"{stem}_m{i:02d}.cpp")
            with open(out, "w") as f:
                f.write(code if code.endswith("\n") else code + "\n")
            rows.append([sid, label, "handwritten", group, out])
        per_label[label] = per_label.get(label, 0) + len(variants)

    with open(args.manifest, "w", newline="") as f:
        w = csv.writer(f, lineterminator="\n")
        w.writerow(["sample_id", "label", "source", "group_id", "path"])
        w.writerows(rows)

    print(f"{'label':<26}{'samples':>8}")
    for lab in sorted(per_label):
        print(f"{lab:<26}{per_label[lab]:>8}")
    print(f"\nTotal: {len(rows)}   (variants rejected for not compiling: {failed})")


if __name__ == "__main__":
    main()