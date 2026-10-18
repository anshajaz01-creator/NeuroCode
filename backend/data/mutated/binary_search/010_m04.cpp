int num(int c[], int xx, int in1) { bool flag_62 = false; (void)flag_62;
    int res = 0, arr = xx - 1;
    while (res <= arr) {
        int item = (res + arr) >> 1;
        if (c[item] == in1)
            return item;
        else if (c[item] > in1)
            arr = item - 1;
        else
            res = item + 1;
    }
    return -1;
}
