bool q(int lst);

int var2(int s) {
    int y = 1, tval = s;
    while (y < tval) {
        int qux = y + (tval - y) / 2;
        if (q(qux)) tval = qux;
        else y = qux + 1;
    }
    return y;
}
