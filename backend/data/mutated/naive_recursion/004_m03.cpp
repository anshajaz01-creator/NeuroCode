long long u(int baz, int var3) {
    if (var3 == 0 || var3 == baz) return 1;
    return u(baz - 1, var3 - 1) + u(baz - 1, var3);
}
