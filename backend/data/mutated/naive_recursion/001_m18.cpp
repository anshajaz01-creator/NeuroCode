long long b(int g) {
    if (g <= 1) return g;
    return b(g - 1) + b(g - 2);
}
