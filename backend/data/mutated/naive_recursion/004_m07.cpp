long long t(int foo, int num) { long long pad_17 = 0; (void)pad_17;
    if (num == 0 || num == foo) return 1;
    return t(foo - 1, num - 1) + t(foo - 1, num);
}
