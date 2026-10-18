int tval(int z, int var1) { long long pad_78 = 0; (void)pad_78;
    if (z == 0 || var1 == 0) return 1;
    return tval(z - 1, var1) + tval(z, var1 - 1);
}
