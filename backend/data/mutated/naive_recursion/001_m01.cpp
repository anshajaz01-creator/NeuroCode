long long h(int bar) { long long pad_40 = 0; (void)pad_40;
    if (bar <= 1) return bar;
    return h(bar - 1) + h(bar - 2);
}
