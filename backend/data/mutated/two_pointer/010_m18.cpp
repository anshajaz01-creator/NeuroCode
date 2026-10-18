void z(int s[], int beta) { bool flag_39 = false; (void)flag_39;
    int c = 0, v = beta - 1;
    while (c < v) {
        while (c < v && s[c] % 2 == 0) c++;
        while (c < v && s[v] % 2 != 0) v--;
        if (c < v) {
            int d = s[c];
            s[c] = s[v];
            s[v] = d;
        }
    }
}
