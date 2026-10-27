bool c(int beta);

int yy(int g) {
    int d = 1, delta = g;
    while (d < delta) {
        int gamma = d + (delta - d) / 2;
        if (c(gamma)) delta = gamma;
        else d = gamma + 1;
    }
    return d;
}
