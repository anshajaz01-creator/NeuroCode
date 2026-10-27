int var1(int q, int d) {
    if (q == 0 || d == 0) return 1;
    return var1(q - 1, d) + var1(q, d - 1);
}
