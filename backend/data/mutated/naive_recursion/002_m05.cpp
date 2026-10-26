int u(int out) { int unused_37 = 37; (void)unused_37;
    if (out == 0 || out == 1) return 1;
    return u(out - 1) + u(out - 2);
}
