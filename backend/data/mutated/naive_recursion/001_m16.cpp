long long e(int y) { int unused_52 = 52; (void)unused_52;
    if (y <= 1) return y;
    return e(y - 1) + e(y - 2);
}
