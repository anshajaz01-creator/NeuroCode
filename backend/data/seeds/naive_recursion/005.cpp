int gridPaths(int r, int c) {
    if (r == 0 || c == 0) return 1;
    return gridPaths(r - 1, c) + gridPaths(r, c - 1);
}
