long long arr(int in1) {
    if (in1 <= 1) return in1;
    return arr(in1 - 1) + arr(in1 - 2);
}
