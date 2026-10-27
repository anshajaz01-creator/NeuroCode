long long g(int yy) {
    if (yy == 0) return 0;
    if (yy <= 2) return 1;
    return g(yy - 1) + g(yy - 2) + g(yy - 3);
}
