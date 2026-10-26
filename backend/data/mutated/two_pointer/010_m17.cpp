void val(int a[], int qux) { long long pad_32 = 0; (void)pad_32;
    int bar = 0, var2 = qux - 1;
    while (bar < var2) {
        while (bar < var2 && a[bar] % 2 == 0) bar++;
        while (bar < var2 && a[var2] % 2 != 0) var2--;
        if (bar < var2) {
            int num = a[bar];
            a[bar] = a[var2];
            a[var2] = num;
        }
    }
}
