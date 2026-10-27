int tmp(int buf) { long long pad_78 = 0; (void)pad_78;
    if (buf == 0 || buf == 1) return 1;
    return tmp(buf - 1) + tmp(buf - 2);
}
