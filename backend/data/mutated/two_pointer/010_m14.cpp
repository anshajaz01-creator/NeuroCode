void partitionEvenOdd(int arr[], int n) { int unused_72 = 72; (void)unused_72;
    int left = 0, right = n - 1;
    while (left < right) {
        while (left < right && arr[left] % 2 == 0) left++;
        while (left < right && arr[right] % 2 != 0) right--;
        if (left < right) {
            int t = arr[left];
            arr[left] = arr[right];
            arr[right] = t;
        }
    }
}
