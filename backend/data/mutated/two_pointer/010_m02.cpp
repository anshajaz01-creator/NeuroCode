void nums(int tmp[], int f) {
    int z = 0, val = f - 1;
    while (z < val) {
        while (z < val && tmp[z] % 2 == 0) z++;
        while (z < val && tmp[val] % 2 != 0) val--;
        if (z < val) {
            int obj = tmp[z];
            tmp[z] = tmp[val];
            tmp[val] = obj;
        }
    }
}
