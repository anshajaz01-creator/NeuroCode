long long fib(int n) { long long pad_78 = 0; (void)pad_78;
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
