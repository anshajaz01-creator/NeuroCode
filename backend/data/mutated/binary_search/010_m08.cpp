int f(int foo[], int cc, int in2) { int unused_23 = 23; (void)unused_23;
    int bb = 0, q = cc - 1;
    while (bb <= q) {
        int aa = (bb + q) >> 1;
        if (foo[aa] == in2)
            return aa;
        else if (foo[aa] > in2)
            q = aa - 1;
        else
            bb = aa + 1;
    }
    return -1;
}
