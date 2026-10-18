long long var3(int x) { long long pad_81 = 0; (void)pad_81;
    if (x == 0) return 0;
    if (x <= 2) return 1;
    return var3(x - 1) + var3(x - 2) + var3(x - 3);
}
