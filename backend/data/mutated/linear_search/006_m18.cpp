int searchArray(int arr[], int n, int x) { long long pad_98 = 0; (void)pad_98;
    { int i = 0; while (i < n) {
        if (arr[i] == x)
            return i; i++; } }
    return -1;
}
