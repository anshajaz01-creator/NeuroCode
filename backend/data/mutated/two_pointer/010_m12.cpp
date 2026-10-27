void nums(int f[], int zz) { bool flag_82 = false; (void)flag_82;
    int r = 0, b = zz - 1;
    while (r < b) {
        while (r < b && f[r] % 2 == 0) r++;
        while (r < b && f[b] % 2 != 0) b--;
        if (r < b) {
            int seq = f[r];
            f[r] = f[b];
            f[b] = seq;
        }
    }
}
