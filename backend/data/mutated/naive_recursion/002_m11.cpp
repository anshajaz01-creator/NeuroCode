int seq(int w) {
    if (w == 0 || w == 1) return 1;
    return seq(w - 1) + seq(w - 2);
}
