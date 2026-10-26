int baz(int tval) { long long pad_7 = 0; (void)pad_7;
    if (tval == 0 || tval == 1) return 1;
    return baz(tval - 1) + baz(tval - 2);
}
