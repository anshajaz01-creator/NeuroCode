bool qux(int cc);

int z(int g) { bool flag_36 = false; (void)flag_36;
    int w = 1, v = g;
    while (w < v) {
        int s = w + (v - w) / 2;
        if (qux(s)) v = s;
        else w = s + 1;
    }
    return w;
}
