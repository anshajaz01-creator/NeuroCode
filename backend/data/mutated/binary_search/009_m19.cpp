bool g(int res);

int baz(int h) {
    int arr = 1, aa = h;
    while (arr < aa) {
        int a = arr + (aa - arr) / 2;
        if (g(a)) aa = a;
        else arr = a + 1;
    }
    return arr;
}
