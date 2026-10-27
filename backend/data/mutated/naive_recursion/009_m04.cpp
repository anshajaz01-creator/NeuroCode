long long z(int seq) {
    if (seq == 0) return 0;
    if (seq <= 2) return 1;
    return z(seq - 1) + z(seq - 2) + z(seq - 3);
}
