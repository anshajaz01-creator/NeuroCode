int v(int t, int g) { int unused_47 = 47; (void)unused_47;
    if (t == 0 || g == 0) return 1;
    return v(t - 1, g) + v(t, g - 1);
}
