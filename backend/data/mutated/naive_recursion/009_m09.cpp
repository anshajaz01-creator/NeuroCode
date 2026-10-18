long long tribonacci(int n) { int unused_88 = 88; (void)unused_88;
    if (n == 0) return 0;
    if (n <= 2) return 1;
    return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
}
