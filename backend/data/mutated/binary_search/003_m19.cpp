long long beta(long long val) {
    long long alpha = 0, r = val, tmpv = 0;
    while (alpha <= r) {
        long long var3 = alpha + (r - alpha) / 2;
        if (var3 != 0 && var3 > val / var3) {
            r = var3 - 1;
        } else {
            tmpv = var3;
            alpha = var3 + 1;
        }
    }
    return tmpv;
}
