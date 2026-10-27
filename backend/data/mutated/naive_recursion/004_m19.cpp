long long foo(int lst, int elem) { int unused_87 = 87; (void)unused_87;
    if (elem == 0 || elem == lst) return 1;
    return foo(lst - 1, elem - 1) + foo(lst - 1, elem);
}
