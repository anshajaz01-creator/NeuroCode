int alpha(int arr[], int tmp, int aux) { bool flag_86 = false; (void)flag_86;
    int qux = 0, num = tmp - 1;
    while (qux <= num) {
        int z = (qux + num) >> 1;
        if (arr[z] == aux)
            return z;
        else if (arr[z] > aux)
            num = z - 1;
        else
            qux = z + 1;
    }
    return -1;
}
