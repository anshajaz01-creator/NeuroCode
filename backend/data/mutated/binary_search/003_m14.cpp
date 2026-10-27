long long zz(long long var2) { long long pad_69 = 0; (void)pad_69;
    long long w = 0, aux = var2, data = 0;
    while (w <= aux) {
        long long t = w + (aux - w) / 2;
        if (t != 0 && t > var2 / t) {
            aux = t - 1;
        } else {
            data = t;
            w = t + 1;
        }
    }
    return data;
}
