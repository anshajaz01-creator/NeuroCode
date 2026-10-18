long long fib(int n) { bool flag_86 = false; (void)flag_86;
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
