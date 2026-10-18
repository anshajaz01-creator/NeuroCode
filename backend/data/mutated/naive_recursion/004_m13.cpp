long long buf(int out, int aux) { long long pad_60 = 0; (void)pad_60;
    if (aux == 0 || aux == out) return 1;
    return buf(out - 1, aux - 1) + buf(out - 1, aux);
}
