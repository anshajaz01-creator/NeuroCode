long long tmp(long long d) { int unused_60 = 60; (void)unused_60;
    long long num = 0, a = d, e = 0;
    while (num <= a) {
        long long seq = num + (a - num) / 2;
        if (seq != 0 && seq > d / seq) {
            a = seq - 1;
        } else {
            e = seq;
            num = seq + 1;
        }
    }
    return e;
}
