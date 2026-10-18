"""
Produce the AST JSON that FeatureExtractor consumes.

This is the TRAINING-TIME producer. At inference time the same JSON comes from
T4's C++ engine. The two must agree on node type names and field names or the
model sees different features in production than it trained on.

Schema (one node):
  { "type": <clang cursor kind name>, "spelling": str, "dtype": str,
    "line": int, "op": str, "tokens": str, "has_else": bool,
    "base_text": str, "index_text": str, "children": [...] }

Usage:
  python3 extract_ast.py file.cpp > file.ast.json
"""
import json
import sys

import clang.cindex as ci

MAX_TOKENS = 40


def _tokens(cursor):
    try:
        toks = [t.spelling for t in cursor.get_tokens()]
        return " ".join(toks[:MAX_TOKENS])
    except Exception:
        return ""


def _binary_op(cursor):
    """libclang does not expose the operator directly. Read it from the tokens
    between the end of the left operand and the start of the right one."""
    try:
        kids = list(cursor.get_children())
        if len(kids) != 2:
            return ""
        lhs_end = kids[0].extent.end.offset
        rhs_start = kids[1].extent.start.offset
        for t in cursor.get_tokens():
            if t.extent.start.offset >= lhs_end and t.extent.end.offset <= rhs_start:
                return t.spelling
    except Exception:
        pass
    return ""


def to_node(cursor, depth=0, max_depth=60):
    kind = cursor.kind.name
    node = {
        "type": kind,
        "spelling": cursor.spelling or "",
        "line": cursor.location.line,
        "children": [],
    }

    try:
        t = cursor.type.spelling
        if t and t != "NoneType":
            node["dtype"] = t
    except Exception:
        pass

    if kind in ("FOR_STMT", "WHILE_STMT", "DO_STMT", "CXX_FOR_RANGE_STMT"):
        node["tokens"] = _tokens(cursor)
    if kind == "BINARY_OPERATOR" or kind == "COMPOUND_ASSIGNMENT_OPERATOR":
        node["op"] = _binary_op(cursor)
    if kind == "IF_STMT":
        node["has_else"] = len(list(cursor.get_children())) >= 3
    if kind == "ARRAY_SUBSCRIPT_EXPR":
        kids = list(cursor.get_children())
        if len(kids) == 2:
            node["base_text"] = _tokens(kids[0]).strip()
            node["index_text"] = _tokens(kids[1]).strip()
    if kind == "CALL_EXPR" and node["spelling"] == "operator[]":
        # vector/map indexing is an overloaded operator call, not ARRAY_SUBSCRIPT_EXPR.
        # children: [base, operator ref, index]
        kids = list(cursor.get_children())
        if len(kids) == 3:
            node["base_text"] = _tokens(kids[0]).strip()
            node["index_text"] = _tokens(kids[2]).strip()
    if kind == "CALL_EXPR" and not node["spelling"]:
        # member calls sometimes have empty spelling, pull the member name
        for ch in cursor.get_children():
            if ch.kind.name == "MEMBER_REF_EXPR":
                node["spelling"] = ch.spelling
                break

    if depth < max_depth:
        for ch in cursor.get_children():
            node["children"].append(to_node(ch, depth + 1, max_depth))

    return node


import glob, os

def builtin_includes():
    """The pip libclang wheel ships no builtin headers, so stddef.h is not
    found and the whole translation unit fails to parse. Point it at the
    system GCC ones. Adjust GCC_VERSION if your box differs."""
    inc = []
    for d in sorted(glob.glob("/usr/lib/gcc/*/*/include"), reverse=True):
        inc.append("-I" + d)
        break
    for d in sorted(glob.glob("/usr/include/c++/*"), reverse=True):
        inc.append("-I" + d)
        for sub in glob.glob(d + "/*-linux-gnu"):
            inc.append("-I" + sub)
        break
    inc.append("-I/usr/include")
    return inc


def parse_file(path, extra_args=None):
    args = ["-std=c++17", "-fsyntax-only"] + builtin_includes() + (extra_args or [])
    idx = ci.Index.create()
    tu = idx.parse(path, args=args)
    hard = [d for d in tu.diagnostics if d.severity >= ci.Diagnostic.Error]
    root = {"type": "TranslationUnit", "spelling": path, "line": 0, "children": []}
    for ch in tu.cursor.get_children():
        # skip anything from system headers
        if ch.location.file and ch.location.file.name == path:
            root["children"].append(to_node(ch))
    return root, hard


if __name__ == "__main__":
    ast, errs = parse_file(sys.argv[1])
    if errs and "--strict" in sys.argv:
        sys.stderr.write(f"{len(errs)} parse errors\n")
        sys.exit(1)
    json.dump(ast, sys.stdout)