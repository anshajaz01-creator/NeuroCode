int var3(int f, int zz) { bool flag_10 = false; (void)flag_10;
    if (f == 0 || zz == 0) return 1;
    return var3(f - 1, zz) + var3(f, zz - 1);
}
