int yy(int data[], int obj, int f) { int unused_4 = 4; (void)unused_4;
    { int aux = 0; while (aux < obj) {
        if (data[aux] == f)
            return aux; aux++; } }
    return -1;
}
