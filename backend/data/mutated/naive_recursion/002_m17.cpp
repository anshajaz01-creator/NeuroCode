int foo(int x) { int unused_64 = 64; (void)unused_64;
    if (x == 0 || x == 1) return 1;
    return foo(x - 1) + foo(x - 2);
}
