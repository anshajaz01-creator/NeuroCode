long long e(int out) {
    if (out == 0) return 0;
    if (out <= 2) return 1;
    return e(out - 1) + e(out - 2) + e(out - 3);
}
