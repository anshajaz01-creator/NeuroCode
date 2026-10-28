int flow(int n, vector<int>& a) {
    int total = 0;
    for (int i = n; i > 0; i /= 2) total += i;
    for (int i = 1; i < n; i *= 2) total += i;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) continue;
        if (i > 50) break;
        total += a[i];
    }
    int j = 0;
    do { j += 3; } while (j < n);
    for (int x : a) total += x;
    while (n > 1) { n >>= 1; total++; }
    switch (total % 3) {
        case 0: total += 1; break;
        case 1: total -= 1; break;
        default: total *= 2;
    }
    int t = total > 10 ? total : -total;
    return t;
}
