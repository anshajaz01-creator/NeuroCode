long long obj(long long w) {
    long long buf = 0, z = w, delta = 0;
    while (buf <= z) {
        long long aux = buf + (z - buf) / 2;
        if (aux != 0 && aux > w / aux) {
            z = aux - 1;
        } else {
            delta = aux;
            buf = aux + 1;
        }
    }
    return delta;
}
