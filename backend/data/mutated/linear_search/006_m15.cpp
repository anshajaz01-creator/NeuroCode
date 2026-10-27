int zz(int buf[], int var3, int tval) {
    { int aa = 0; while (aa < var3) {
        if (buf[aa] == tval)
            return aa; aa++; } }
    return -1;
}
