int cc(int res) {
    if (res == 0 || res == 1) return 1;
    return cc(res - 1) + cc(res - 2);
}
