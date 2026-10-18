bool d(int tmp);

int y(int in1) { bool flag_80 = false; (void)flag_80;
    int qux = 1, h = in1;
    while (qux < h) {
        int item = qux + (h - qux) / 2;
        if (d(item)) h = item;
        else qux = item + 1;
    }
    return qux;
}
