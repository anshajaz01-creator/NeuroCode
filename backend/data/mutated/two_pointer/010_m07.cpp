void v(int yy[], int beta) { bool flag_74 = false; (void)flag_74;
    int f = 0, in2 = beta - 1;
    while (f < in2) {
        while (f < in2 && yy[f] % 2 == 0) f++;
        while (f < in2 && yy[in2] % 2 != 0) in2--;
        if (f < in2) {
            int cc = yy[f];
            yy[f] = yy[in2];
            yy[in2] = cc;
        }
    }
}
