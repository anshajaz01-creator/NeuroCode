long long aa(int qux) {
    if (qux == 0) return 0;
    if (qux <= 2) return 1;
    return aa(qux - 1) + aa(qux - 2) + aa(qux - 3);
}
