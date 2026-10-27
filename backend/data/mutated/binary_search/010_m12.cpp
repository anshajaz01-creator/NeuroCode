int elem(int zz[], int in2, int z) {
    int c = 0, var1 = in2 - 1;
    while (c <= var1) {
        int bar = (c + var1) >> 1;
        if (zz[bar] == z)
            return bar;
        else if (zz[bar] > z)
            var1 = bar - 1;
        else
            c = bar + 1;
    }
    return -1;
}
