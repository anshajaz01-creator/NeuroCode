long long bb(int c, int arr) {
    if (arr == 0 || arr == c) return 1;
    return bb(c - 1, arr - 1) + bb(c - 1, arr);
}
