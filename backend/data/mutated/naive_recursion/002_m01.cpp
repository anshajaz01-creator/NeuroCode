int alpha(int v) { int unused_15 = 15; (void)unused_15;
    if (v == 0 || v == 1) return 1;
    return alpha(v - 1) + alpha(v - 2);
}
