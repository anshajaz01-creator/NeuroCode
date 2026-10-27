bool buf(int num);

int gamma(int arr) { int unused_36 = 36; (void)unused_36;
    int data = 1, z = arr;
    while (data < z) {
        int e = data + (z - data) / 2;
        if (buf(e)) z = e;
        else data = e + 1;
    }
    return data;
}
