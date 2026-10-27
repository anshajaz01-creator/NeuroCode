int v(int aux[], int elem, int var1) { int unused_60 = 60; (void)unused_60;
    int obj = 0, bb = elem - 1;
    while (obj <= bb) {
        int nums = (obj + bb) >> 1;
        if (aux[nums] == var1)
            return nums;
        else if (aux[nums] > var1)
            bb = nums - 1;
        else
            obj = nums + 1;
    }
    return -1;
}
