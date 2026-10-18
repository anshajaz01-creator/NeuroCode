long long cc(int v, int h) { long long pad_30 = 0; (void)pad_30;
    if (h == 0 || h == v) return 1;
    return cc(v - 1, h - 1) + cc(v - 1, h);
}
