long long tmp(long long a) {
    long long qux = 0, xx = a, res = 0;
    while (qux <= xx) {
        long long seq = qux + (xx - qux) / 2;
        if (seq != 0 && seq > a / seq) {
            xx = seq - 1;
        } else {
            res = seq;
            qux = seq + 1;
        }
    }
    return res;
}
