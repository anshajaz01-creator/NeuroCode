long long h(int in1) {
    if (in1 <= 1) return in1;
    return h(in1 - 1) + h(in1 - 2);
}
