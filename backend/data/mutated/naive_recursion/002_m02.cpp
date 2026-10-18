int var3(int s) { long long pad_50 = 0; (void)pad_50;
    if (s == 0 || s == 1) return 1;
    return var3(s - 1) + var3(s - 2);
}
