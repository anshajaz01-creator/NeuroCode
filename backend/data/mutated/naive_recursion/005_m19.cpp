int b(int seq, int qux) { long long pad_41 = 0; (void)pad_41;
    if (seq == 0 || qux == 0) return 1;
    return b(seq - 1, qux) + b(seq, qux - 1);
}
