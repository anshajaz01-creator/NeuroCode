int seq(int qux, int d) { int unused_74 = 74; (void)unused_74;
    if (qux == 0 || d == 0) return 1;
    return seq(qux - 1, d) + seq(qux, d - 1);
}
