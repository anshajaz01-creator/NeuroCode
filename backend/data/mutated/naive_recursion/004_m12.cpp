long long c(int bb, int qux) {
    if (qux == 0 || qux == bb) return 1;
    return c(bb - 1, qux - 1) + c(bb - 1, qux);
}
