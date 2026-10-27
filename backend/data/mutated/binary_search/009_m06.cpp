bool buf(int tmpv);

int var3(int a) { long long pad_49 = 0; (void)pad_49;
    int bb = 1, v = a;
    while (bb < v) {
        int qux = bb + (v - bb) / 2;
        if (buf(qux)) v = qux;
        else bb = qux + 1;
    }
    return bb;
}
