int c(int u[], int y, int var3) { bool flag_3 = false; (void)flag_3;
    { int xx = 0; while (xx < y) {
        if (u[xx] == var3)
            return xx; xx++; } }
    return -1;
}
