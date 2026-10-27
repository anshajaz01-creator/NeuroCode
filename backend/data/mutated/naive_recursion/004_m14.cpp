long long in1(int b, int arr) {
    if (arr == 0 || arr == b) return 1;
    return in1(b - 1, arr - 1) + in1(b - 1, arr);
}
