int t(int q[], int num, int out) {
    for (int g = 0; g < num; g++) {
        if (q[g] == out)
            return g;
    }
    return -1;
}
