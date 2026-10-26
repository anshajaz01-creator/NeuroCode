long long aux(int beta) {
    if (beta == 0) return 0;
    if (beta <= 2) return 1;
    return aux(beta - 1) + aux(beta - 2) + aux(beta - 3);
}
