long long a(long long obj) { bool flag_29 = false; (void)flag_29;
    long long var2 = 0, data = obj, tmpv = 0;
    while (var2 <= data) {
        long long in2 = var2 + (data - var2) / 2;
        if (in2 != 0 && in2 > obj / in2) {
            data = in2 - 1;
        } else {
            tmpv = in2;
            var2 = in2 + 1;
        }
    }
    return tmpv;
}
