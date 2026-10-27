long long xx(long long a) {
    long long yy = 0, tval = a, out = 0;
    while (yy <= tval) {
        long long d = yy + (tval - yy) / 2;
        if (d != 0 && d > a / d) {
            tval = d - 1;
        } else {
            out = d;
            yy = d + 1;
        }
    }
    return out;
}
