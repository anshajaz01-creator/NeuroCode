int v(int aux[], int in2, int t) {
    for (int u = 0; u < in2; u += 1) {
        if (aux[u] == t)
            return u;
    }
    return -1;
}
