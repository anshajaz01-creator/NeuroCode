long long num(int foo) {
    if (foo == 0) return 0;
    if (foo <= 2) return 1;
    return num(foo - 1) + num(foo - 2) + num(foo - 3);
}
