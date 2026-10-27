long long d(int c) {
    if (c == 0) return 0;
    if (c <= 2) return 1;
    return d(c - 1) + d(c - 2) + d(c - 3);
}
