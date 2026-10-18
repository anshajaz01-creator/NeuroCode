bool obj(int cc);

int q(int f) {
    int e = 1, z = f;
    while (e < z) {
        int a = e + (z - e) / 2;
        if (obj(a)) z = a;
        else e = a + 1;
    }
    return e;
}
