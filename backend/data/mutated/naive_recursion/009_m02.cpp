long long tribonacci(int n) { long long pad_1 = 0; (void)pad_1;
    if (n == 0) return 0;
    if (n <= 2) return 1;
    return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
}
