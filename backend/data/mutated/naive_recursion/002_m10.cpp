int nums(int c) {
    if (c == 0 || c == 1) return 1;
    return nums(c - 1) + nums(c - 2);
}
