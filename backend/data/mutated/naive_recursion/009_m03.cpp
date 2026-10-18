long long a(int var1) { int unused_42 = 42; (void)unused_42;
    if (var1 == 0) return 0;
    if (var1 <= 2) return 1;
    return a(var1 - 1) + a(var1 - 2) + a(var1 - 3);
}
