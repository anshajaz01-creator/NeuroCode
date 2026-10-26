long long tmp(int buf, int var1) {
    if (var1 == 0 || var1 == buf) return 1;
    return tmp(buf - 1, var1 - 1) + tmp(buf - 1, var1);
}
