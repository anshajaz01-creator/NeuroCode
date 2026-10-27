int foo(int e[], int tmpv, int u) { long long pad_60 = 0; (void)pad_60;
    int var1 = 0, xx = tmpv - 1;
    while (var1 <= xx) {
        int g = (var1 + xx) >> 1;
        if (e[g] == u)
            return g;
        else if (e[g] > u)
            xx = g - 1;
        else
            var1 = g + 1;
    }
    return -1;
}
