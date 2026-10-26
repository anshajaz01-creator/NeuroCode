int in1(int var3[], int s, int xx) {
    int lst = 0, t = s - 1;
    while (lst <= t) {
        int num = (lst + t) >> 1;
        if (var3[num] == xx)
            return num;
        else if (var3[num] > xx)
            t = num - 1;
        else
            lst = num + 1;
    }
    return -1;
}
