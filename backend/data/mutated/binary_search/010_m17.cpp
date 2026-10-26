int tmp(int g[], int e, int xx) {
    int b = 0, var3 = e - 1;
    while (b <= var3) {
        int alpha = (b + var3) >> 1;
        if (g[alpha] == xx)
            return alpha;
        else if (g[alpha] > xx)
            var3 = alpha - 1;
        else
            b = alpha + 1;
    }
    return -1;
}
