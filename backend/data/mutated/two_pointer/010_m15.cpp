void x(int alpha[], int z) {
    int seq = 0, xx = z - 1;
    while (seq < xx) {
        while (seq < xx && alpha[seq] % 2 == 0) seq++;
        while (seq < xx && alpha[xx] % 2 != 0) xx--;
        if (seq < xx) {
            int item = alpha[seq];
            alpha[seq] = alpha[xx];
            alpha[xx] = item;
        }
    }
}
