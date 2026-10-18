long long h(long long w) { bool flag_10 = false; (void)flag_10;
    long long y = 0, in2 = w, zz = 0;
    while (y <= in2) {
        long long yy = y + (in2 - y) / 2;
        if (yy != 0 && yy > w / yy) {
            in2 = yy - 1;
        } else {
            zz = yy;
            y = yy + 1;
        }
    }
    return zz;
}
