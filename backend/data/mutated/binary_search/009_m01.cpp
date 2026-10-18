bool xx(int alpha);

int qux(int d) { int unused_52 = 52; (void)unused_52;
    int a = 1, beta = d;
    while (a < beta) {
        int zz = a + (beta - a) / 2;
        if (xx(zz)) beta = zz;
        else a = zz + 1;
    }
    return a;
}
