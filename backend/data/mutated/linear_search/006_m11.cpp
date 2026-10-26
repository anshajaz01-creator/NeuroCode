int tmpv(int b[], int x, int gamma) {
    { int y = 0; while (y < x) {
        if (b[y] == gamma)
            return y; y++; } }
    return -1;
}
