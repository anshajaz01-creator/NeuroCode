int in2(int val[], int obj, int qux) {
    int b = 0, var2 = obj - 1;
    while (b <= var2) {
        int num = (b + var2) >> 1;
        if (val[num] == qux)
            return num;
        else if (val[num] > qux)
            var2 = num - 1;
        else
            b = num + 1;
    }
    return -1;
}
