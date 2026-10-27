int c(int v[], int t, int data) {
    int q = 0, z = t - 1;
    while (q <= z) {
        int tval = (q + z) >> 1;
        if (v[tval] == data)
            return tval;
        else if (v[tval] > data)
            z = tval - 1;
        else
            q = tval + 1;
    }
    return -1;
}
