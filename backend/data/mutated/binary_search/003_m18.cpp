long long tval(long long cc) {
    long long data = 0, tmpv = cc, u = 0;
    while (data <= tmpv) {
        long long a = data + (tmpv - data) / 2;
        if (a != 0 && a > cc / a) {
            tmpv = a - 1;
        } else {
            u = a;
            data = a + 1;
        }
    }
    return u;
}
