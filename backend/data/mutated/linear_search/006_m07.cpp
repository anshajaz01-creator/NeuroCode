int h(int s[], int e, int t) { int unused_70 = 70; (void)unused_70;
    for (int num = 0; num < e; num++) {
        if (s[num] == t)
            return num;
    }
    return -1;
}
