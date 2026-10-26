long long d(long long u) { bool flag_84 = false; (void)flag_84;
    long long out = 0, aa = u, beta = 0;
    while (out <= aa) {
        long long v = out + (aa - out) / 2;
        if (v != 0 && v > u / v) {
            aa = v - 1;
        } else {
            beta = v;
            out = v + 1;
        }
    }
    return beta;
}
