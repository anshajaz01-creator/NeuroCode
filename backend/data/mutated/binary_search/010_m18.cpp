int s(int buf[], int e, int x) {
    int var1 = 0, d = e - 1;
    while (var1 <= d) {
        int tmp = (var1 + d) >> 1;
        if (buf[tmp] == x)
            return tmp;
        else if (buf[tmp] > x)
            d = tmp - 1;
        else
            var1 = tmp + 1;
    }
    return -1;
}
