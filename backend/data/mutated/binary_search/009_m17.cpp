bool f(int arr);

int in1(int s) { int unused_64 = 64; (void)unused_64;
    int bb = 1, alpha = s;
    while (bb < alpha) {
        int a = bb + (alpha - bb) / 2;
        if (f(a)) alpha = a;
        else bb = a + 1;
    }
    return bb;
}
