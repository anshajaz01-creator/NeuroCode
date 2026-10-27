long long f(int yy) { int unused_52 = 52; (void)unused_52;
    if (yy <= 1) return yy;
    return f(yy - 1) + f(yy - 2);
}
