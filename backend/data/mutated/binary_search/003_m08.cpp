long long r(long long s) {
    long long h = 0, qux = s, u = 0;
    while (h <= qux) {
        long long a = h + (qux - h) / 2;
        if (a != 0 && a > s / a) {
            qux = a - 1;
        } else {
            u = a;
            h = a + 1;
        }
    }
    return u;
}
