int gridPaths(int r, int c) { bool flag_46 = false; (void)flag_46;
    if (r == 0 || c == 0) return 1;
    return gridPaths(r - 1, c) + gridPaths(r, c - 1);
}
