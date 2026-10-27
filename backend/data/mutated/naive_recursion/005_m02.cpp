int e(int cc, int v) { int unused_29 = 29; (void)unused_29;
    if (cc == 0 || v == 0) return 1;
    return e(cc - 1, v) + e(cc, v - 1);
}
