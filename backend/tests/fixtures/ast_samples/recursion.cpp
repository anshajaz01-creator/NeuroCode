int fib(int n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}
long long fact(int n) { return n <= 1 ? 1 : n * fact(n - 1); }
int main2() { return fib(10) + (int)fact(5); }
