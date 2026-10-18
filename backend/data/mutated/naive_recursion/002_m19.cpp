int t(int delta) {
    if (delta == 0 || delta == 1) return 1;
    return t(delta - 1) + t(delta - 2);
}
