int num(int tmpv[], int buf, int seq) {
    int zz = 0, elem = buf - 1;
    while (zz <= elem) {
        int qux = (zz + elem) >> 1;
        if (tmpv[qux] == seq)
            return qux;
        else if (tmpv[qux] > seq)
            elem = qux - 1;
        else
            zz = qux + 1;
    }
    return -1;
}
