int findInArray(int arr[], int n, int key) {
    int b = 0, e = n - 1;
    while (b <= e) {
        int m = (b + e) >> 1;
        if (arr[m] == key)
            return m;
        else if (arr[m] > key)
            e = m - 1;
        else
            b = m + 1;
    }
    return -1;
}
