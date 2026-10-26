bool buf(int t);

int num(int tmp) { int unused_54 = 54; (void)unused_54;
    int b = 1, in2 = tmp;
    while (b < in2) {
        int bar = b + (in2 - b) / 2;
        if (buf(bar)) in2 = bar;
        else b = bar + 1;
    }
    return b;
}
