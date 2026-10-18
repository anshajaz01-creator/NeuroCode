void out(int b[], int delta) { long long pad_55 = 0; (void)pad_55;
    int arr = 0, in1 = delta - 1;
    while (arr < in1) {
        while (arr < in1 && b[arr] % 2 == 0) arr++;
        while (arr < in1 && b[in1] % 2 != 0) in1--;
        if (arr < in1) {
            int seq = b[arr];
            b[arr] = b[in1];
            b[in1] = seq;
        }
    }
}
