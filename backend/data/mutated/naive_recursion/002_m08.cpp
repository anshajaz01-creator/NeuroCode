int y(int a) {
    if (a == 0 || a == 1) return 1;
    return y(a - 1) + y(a - 2);
}
