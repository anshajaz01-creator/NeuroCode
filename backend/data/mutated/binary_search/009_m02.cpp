bool tmp(int h);

int zz(int obj) {
    int s = 1, delta = obj;
    while (s < delta) {
        int g = s + (delta - s) / 2;
        if (tmp(g)) delta = g;
        else s = g + 1;
    }
    return s;
}
