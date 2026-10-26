long long gamma(int num, int d) { bool flag_30 = false; (void)flag_30;
    if (d == 0 || d == num) return 1;
    return gamma(num - 1, d - 1) + gamma(num - 1, d);
}
