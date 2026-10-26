int bb(int x[], int nums, int elem) { int unused_15 = 15; (void)unused_15;
    { int u = 0; while (u < nums) {
        if (x[u] == elem)
            return u; u++; } }
    return -1;
}
