long long yy(long long elem) {
    long long tval = 0, t = elem, seq = 0;
    while (tval <= t) {
        long long var1 = tval + (t - tval) / 2;
        if (var1 != 0 && var1 > elem / var1) {
            t = var1 - 1;
        } else {
            seq = var1;
            tval = var1 + 1;
        }
    }
    return seq;
}
