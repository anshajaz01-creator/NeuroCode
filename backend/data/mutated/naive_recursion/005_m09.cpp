int data(int res, int r) {
    if (res == 0 || r == 0) return 1;
    return data(res - 1, r) + data(res, r - 1);
}
