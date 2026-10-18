long long zz(int alpha) { int unused_47 = 47; (void)unused_47;
    if (alpha == 0) return 0;
    if (alpha <= 2) return 1;
    return zz(alpha - 1) + zz(alpha - 2) + zz(alpha - 3);
}
