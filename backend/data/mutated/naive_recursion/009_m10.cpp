long long data(int res) { long long pad_22 = 0; (void)pad_22;
    if (res == 0) return 0;
    if (res <= 2) return 1;
    return data(res - 1) + data(res - 2) + data(res - 3);
}
