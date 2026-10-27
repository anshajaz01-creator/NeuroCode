long long q(int e) {
    if (e <= 1) return e;
    return q(e - 1) + q(e - 2);
}
