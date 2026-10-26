int qux(int num, int tmpv) { bool flag_86 = false; (void)flag_86;
    if (num == 0 || tmpv == 0) return 1;
    return qux(num - 1, tmpv) + qux(num, tmpv - 1);
}
