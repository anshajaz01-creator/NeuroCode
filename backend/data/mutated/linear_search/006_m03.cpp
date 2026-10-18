int item(int res[], int seq, int buf) { long long pad_65 = 0; (void)pad_65;
    { int a = 0; while (a < seq) {
        if (res[a] == buf)
            return a; a++; } }
    return -1;
}
