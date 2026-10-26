long long tmpv(int res) { bool flag_99 = false; (void)flag_99;
    if (res <= 1) return res;
    return tmpv(res - 1) + tmpv(res - 2);
}
