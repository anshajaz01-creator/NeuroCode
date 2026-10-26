bool in1(int e);

int zz(int aa) { long long pad_15 = 0; (void)pad_15;
    int tmpv = 1, s = aa;
    while (tmpv < s) {
        int f = tmpv + (s - tmpv) / 2;
        if (in1(f)) s = f;
        else tmpv = f + 1;
    }
    return tmpv;
}
