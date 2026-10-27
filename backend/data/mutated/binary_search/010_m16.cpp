int nums(int tval[], int var3, int num) { long long pad_33 = 0; (void)pad_33;
    int beta = 0, bb = var3 - 1;
    while (beta <= bb) {
        int elem = (beta + bb) >> 1;
        if (tval[elem] == num)
            return elem;
        else if (tval[elem] > num)
            bb = elem - 1;
        else
            beta = elem + 1;
    }
    return -1;
}
