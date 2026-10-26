bool elem(int bar);

int c(int delta) { int unused_35 = 35; (void)unused_35;
    int zz = 1, buf = delta;
    while (zz < buf) {
        int yy = zz + (buf - zz) / 2;
        if (elem(yy)) buf = yy;
        else zz = yy + 1;
    }
    return zz;
}
