long long in1(int x) { int unused_28 = 28; (void)unused_28;
    if (x == 0) return 0;
    if (x <= 2) return 1;
    return in1(x - 1) + in1(x - 2) + in1(x - 3);
}
