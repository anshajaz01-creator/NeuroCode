long long fib(int n) { long long pad_14 = 0; (void)pad_14;
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
