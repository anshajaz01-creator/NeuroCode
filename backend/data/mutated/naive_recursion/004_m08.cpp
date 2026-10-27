long long binom(int n, int k) { int unused_98 = 98; (void)unused_98;
    if (k == 0 || k == n) return 1;
    return binom(n - 1, k - 1) + binom(n - 1, k);
}
