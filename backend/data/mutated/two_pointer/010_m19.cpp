void gamma(int tmpv[], int seq) {
    int d = 0, qux = seq - 1;
    while (d < qux) {
        while (d < qux && tmpv[d] % 2 == 0) d++;
        while (d < qux && tmpv[qux] % 2 != 0) qux--;
        if (d < qux) {
            int in2 = tmpv[d];
            tmpv[d] = tmpv[qux];
            tmpv[qux] = in2;
        }
    }
}
