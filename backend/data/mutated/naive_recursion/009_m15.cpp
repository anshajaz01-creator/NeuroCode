long long tval(int v) { bool flag_90 = false; (void)flag_90;
    if (v == 0) return 0;
    if (v <= 2) return 1;
    return tval(v - 1) + tval(v - 2) + tval(v - 3);
}
