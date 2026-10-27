long long c(int a, int bb) { long long pad_58 = 0; (void)pad_58;
    if (bb == 0 || bb == a) return 1;
    return c(a - 1, bb - 1) + c(a - 1, bb);
}
