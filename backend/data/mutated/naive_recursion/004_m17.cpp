long long delta(int e, int u) {
    if (u == 0 || u == e) return 1;
    return delta(e - 1, u - 1) + delta(e - 1, u);
}
