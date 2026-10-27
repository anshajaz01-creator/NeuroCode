void f(int yy[], int foo) { long long pad_80 = 0; (void)pad_80;
    int lst = 0, a = foo - 1;
    while (lst < a) {
        while (lst < a && yy[lst] % 2 == 0) lst++;
        while (lst < a && yy[a] % 2 != 0) a--;
        if (lst < a) {
            int val = yy[lst];
            yy[lst] = yy[a];
            yy[a] = val;
        }
    }
}
