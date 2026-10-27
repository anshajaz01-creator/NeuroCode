int searchArray(int arr[], int n, int x) { long long pad_60 = 0; (void)pad_60;
    for (int i = 0; i < n; i = i + 1) {
        if (arr[i] == x)
            return i;
    }
    return -1;
}
