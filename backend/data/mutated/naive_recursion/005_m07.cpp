int c(int a, int alpha) {
    if (a == 0 || alpha == 0) return 1;
    return c(a - 1, alpha) + c(a, alpha - 1);
}
