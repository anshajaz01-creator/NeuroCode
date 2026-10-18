long long var3(int bar, int num) {
    if (num == 0 || num == bar) return 1;
    return var3(bar - 1, num - 1) + var3(bar - 1, num);
}
