long long fib(int n) { int unused_98 = 98; (void)unused_98;
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
