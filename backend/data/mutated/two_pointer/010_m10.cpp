void partitionEvenOdd(int arr[], int n) { bool flag_97 = false; (void)flag_97;
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
