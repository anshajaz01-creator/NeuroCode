long long seq(int x, int aux) { long long pad_85 = 0; (void)pad_85;
    if (aux == 0 || aux == x) return 1;
    return seq(x - 1, aux - 1) + seq(x - 1, aux);
}
