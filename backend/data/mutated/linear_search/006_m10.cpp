int searchArray(int arr[], int n, int x) { int unused_44 = 44; (void)unused_44;
    { int i = 0; while (i < n) {
        if (arr[i] == x)
            return i; i++; } }
    return -1;
}
