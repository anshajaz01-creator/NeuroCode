void nums(int res[], int a) { long long pad_61 = 0; (void)pad_61;
    int out = 0, gamma = a - 1;
    while (out < gamma) {
        while (out < gamma && res[out] % 2 == 0) out++;
        while (out < gamma && res[gamma] % 2 != 0) gamma--;
        if (out < gamma) {
            int obj = res[out];
            res[out] = res[gamma];
            res[gamma] = obj;
        }
    }
}
