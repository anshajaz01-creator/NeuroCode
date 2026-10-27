int out(int aa, int v) { int unused_35 = 35; (void)unused_35;
    if (aa == 0 || v == 0) return 1;
    return out(aa - 1, v) + out(aa, v - 1);
}
