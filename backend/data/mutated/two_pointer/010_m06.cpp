void lst(int bar[], int u) { bool flag_25 = false; (void)flag_25;
    int v = 0, t = u - 1;
    while (v < t) {
        while (v < t && bar[v] % 2 == 0) v++;
        while (v < t && bar[t] % 2 != 0) t--;
        if (v < t) {
            int tval = bar[v];
            bar[v] = bar[t];
            bar[t] = tval;
        }
    }
}
