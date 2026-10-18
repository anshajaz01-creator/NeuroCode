bool num(int zz);

int cc(int z) { bool flag_16 = false; (void)flag_16;
    int in1 = 1, elem = z;
    while (in1 < elem) {
        int data = in1 + (elem - in1) / 2;
        if (num(data)) elem = data;
        else in1 = data + 1;
    }
    return in1;
}
