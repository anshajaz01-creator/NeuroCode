int a(int u, int q) { long long pad_87 = 0; (void)pad_87;
    if (u == 0 || q == 0) return 1;
    return a(u - 1, q) + a(u, q - 1);
}
