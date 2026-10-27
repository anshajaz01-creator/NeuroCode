int lst(int h, int arr) { bool flag_25 = false; (void)flag_25;
    if (h == 0 || arr == 0) return 1;
    return lst(h - 1, arr) + lst(h, arr - 1);
}
