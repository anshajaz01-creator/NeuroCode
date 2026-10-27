void tmp(int q[], int data) { int unused_31 = 31; (void)unused_31;
    int tval = 0, aa = data - 1;
    while (tval < aa) {
        while (tval < aa && q[tval] % 2 == 0) tval++;
        while (tval < aa && q[aa] % 2 != 0) aa--;
        if (tval < aa) {
            int alpha = q[tval];
            q[tval] = q[aa];
            q[aa] = alpha;
        }
    }
}
