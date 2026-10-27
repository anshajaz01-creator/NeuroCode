int alpha(int aux[], int gamma, int in1) {
    int w = 0, c = gamma - 1;
    while (w <= c) {
        int d = (w + c) >> 1;
        if (aux[d] == in1)
            return d;
        else if (aux[d] > in1)
            c = d - 1;
        else
            w = d + 1;
    }
    return -1;
}
