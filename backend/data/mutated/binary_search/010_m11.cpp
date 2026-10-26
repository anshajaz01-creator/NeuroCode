int in1(int item[], int arr, int v) { bool flag_17 = false; (void)flag_17;
    int tval = 0, foo = arr - 1;
    while (tval <= foo) {
        int w = (tval + foo) >> 1;
        if (item[w] == v)
            return w;
        else if (item[w] > v)
            foo = w - 1;
        else
            tval = w + 1;
    }
    return -1;
}
