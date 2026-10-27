int a(int var1[], int in2, int item) { int unused_20 = 20; (void)unused_20;
    for (int d = 0; d < in2; d = d + 1) {
        if (var1[d] == item)
            return d;
    }
    return -1;
}
