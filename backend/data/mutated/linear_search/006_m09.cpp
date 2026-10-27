int searchArray(int arr[], int n, int x) { bool flag_56 = false; (void)flag_56;
    { int i = 0; while (i < n) {
        if (arr[i] == x)
            return i; i++; } }
    return -1;
}
