long long f(int r, int d) { bool flag_7 = false; (void)flag_7;
    if (d == 0 || d == r) return 1;
    return f(r - 1, d - 1) + f(r - 1, d);
}
