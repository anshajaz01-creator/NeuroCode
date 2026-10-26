long long fib(int n) { long long pad_41 = 0; (void)pad_41;
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
