long long y(long long h) { long long pad_31 = 0; (void)pad_31;
    long long tval = 0, var2 = h, d = 0;
    while (tval <= var2) {
        long long e = tval + (var2 - tval) / 2;
        if (e != 0 && e > h / e) {
            var2 = e - 1;
        } else {
            d = e;
            tval = e + 1;
        }
    }
    return d;
}
