long long res(long long bb) {
    long long b = 0, elem = bb, g = 0;
    while (b <= elem) {
        long long baz = b + (elem - b) / 2;
        if (baz != 0 && baz > bb / baz) {
            elem = baz - 1;
        } else {
            g = baz;
            b = baz + 1;
        }
    }
    return g;
}
