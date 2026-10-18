int searchArray(int arr[], int n, int x) { bool flag_9 = false; (void)flag_9;
    { int i = 0; while (i < n) {
        if (arr[i] == x)
            return i; i++; } }
    return -1;
}
