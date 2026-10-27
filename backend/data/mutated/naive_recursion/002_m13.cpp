int val(int u) { int unused_14 = 14; (void)unused_14;
    if (u == 0 || u == 1) return 1;
    return val(u - 1) + val(u - 2);
}
