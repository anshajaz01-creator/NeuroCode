#!/usr/bin/env python3
"""
Sanity check the 48 features before writing the C++ training code.

Trains a plain softmax (multinomial logistic) regression in numpy on
data/dataset.jsonl, using the manifest's train split and standardization from
train statistics only. Reports val/test accuracy, per-class test accuracy and
the most common confusions.

It also runs a grouped 5-fold cross-validation (no group in two folds), which is
far less noisy than the single test split when a class has only a few test groups,
and compares the v1 features (first 48) against all of them.

This is NOT the project model. It answers one question: do the features
separate the classes at all? The LibTorch MLP should beat this number.

Run from backend/:
  python3 tools/baseline_check.py
"""
import json
import sys
from collections import Counter

import numpy as np


def load(path):
    rows = [json.loads(l) for l in open(path)]
    labels = sorted({r["label"] for r in rows})
    li = {l: i for i, l in enumerate(labels)}
    X = np.array([r["features"] for r in rows], dtype=np.float64)
    y = np.array([li[r["label"]] for r in rows])
    s = np.array([r["split"] for r in rows])
    src = np.array([r["source"] for r in rows])
    return X, y, s, src, labels


def train_softmax(X, y, k, epochs=400, lr=0.5, l2=1e-3):
    n, d = X.shape
    W = np.zeros((d, k)); b = np.zeros(k)
    Y = np.eye(k)[y]
    for _ in range(epochs):
        z = X @ W + b
        z -= z.max(1, keepdims=True)
        p = np.exp(z); p /= p.sum(1, keepdims=True)
        g = (p - Y) / n
        W -= lr * (X.T @ g + l2 * W)
        b -= lr * g.sum(0)
    return W, b


def main():
    path = sys.argv[1] if len(sys.argv) > 1 else "data/dataset.jsonl"
    X, y, s, src, labels = load(path)
    k = len(labels)
    tr, va, te = s == "train", s == "val", s == "test"

    # standardize with TRAIN statistics only (same rule the real model must follow)
    mu = X[tr].mean(0); sd = X[tr].std(0); sd[sd == 0] = 1.0
    Z = (X - mu) / sd

    dead = [i for i in range(X.shape[1]) if X[:, i].max() == 0]

    W, b = train_softmax(Z[tr], y[tr], k)
    pred = (Z @ W + b).argmax(1)

    acc = lambda m: (pred[m] == y[m]).mean() if m.any() else float("nan")
    print(f"samples: train {tr.sum()}, val {va.sum()}, test {te.sum()}, classes {k}")
    print(f"chance (always predict largest class): {np.bincount(y[tr]).max() / tr.sum():.1%}")
    print(f"\ntrain acc {acc(tr):.1%}   val acc {acc(va):.1%}   test acc {acc(te):.1%}")

    print(f"\n{'label':<26}{'test n':>8}{'test acc':>10}")
    for i, lab in enumerate(labels):
        m = te & (y == i)
        print(f"{lab:<26}{m.sum():>8}{acc(m):>10.0%}")

    for name in ("handwritten", "codecontests"):
        m = te & (src == name)
        if m.any():
            print(f"test acc on {name}: {acc(m):.1%} ({m.sum()} samples)")

    conf = Counter((labels[a], labels[p]) for a, p in zip(y[te], pred[te]) if a != p)
    if conf:
        print("\nmost common test confusions (true -> predicted):")
        for (a, p), c in conf.most_common(8):
            print(f"  {c:>4}  {a} -> {p}")

    # grouped 5-fold CV: every group is tested exactly once, never trained on in that fold
    rows = [json.loads(l) for l in open(path)]
    g = np.array([r["group_id"] for r in rows])
    groups = sorted(set(g))
    np.random.default_rng(0).shuffle(groups)
    fold_of = {gg: i % 5 for i, gg in enumerate(groups)}
    f = np.array([fold_of[x] for x in g])
    print("\ngrouped 5-fold cross-validation (more reliable than the single split):")
    sets = [("all features", slice(0, X.shape[1]))]
    if X.shape[1] > 48:
        sets.insert(0, ("v1 (first 48)", slice(0, 48)))
    for name, cols in sets:
        cv = np.zeros(len(y), int)
        for k_ in range(5):
            trm, tem = f != k_, f == k_
            Xs = X[:, cols]
            m_ = Xs[trm].mean(0); s_ = Xs[trm].std(0); s_[s_ == 0] = 1.0
            Zs = (Xs - m_) / s_
            W2, b2 = train_softmax(Zs[trm], y[trm], k)
            cv[tem] = (Zs[tem] @ W2 + b2).argmax(1)
        per = "  ".join(f"{labels[i][:14]} {(cv[y == i] == i).mean():.0%}" for i in range(k))
        print(f"  {name:<15} {(cv == y).mean():.1%}")
        print(f"      {per}")

    if dead:
        sys.path.insert(0, "tools")
        import features as F
        print("\nfeatures that are zero in every sample:",
              ", ".join(F.FEATURE_NAMES[i] for i in dead))

if __name__ == "__main__":
    main()