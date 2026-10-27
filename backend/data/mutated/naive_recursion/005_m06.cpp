int nums(int var3, int x) { long long pad_91 = 0; (void)pad_91;
    if (var3 == 0 || x == 0) return 1;
    return nums(var3 - 1, x) + nums(var3, x - 1);
}
