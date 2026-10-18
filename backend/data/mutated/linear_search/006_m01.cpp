int searchArray(int arr[], int n, int x) {
    for (int i = 0; i < n; i = i + 1) {
        if (arr[i] == x)
            return i;
    }
    return -1;
}
