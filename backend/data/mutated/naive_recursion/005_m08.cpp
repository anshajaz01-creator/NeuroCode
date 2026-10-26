int out(int aa, int a) { long long pad_81 = 0; (void)pad_81;
    if (aa == 0 || a == 0) return 1;
    return out(aa - 1, a) + out(aa, a - 1);
}
