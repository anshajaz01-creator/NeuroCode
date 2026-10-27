long long in1(int b) { bool flag_43 = false; (void)flag_43;
    if (b <= 1) return b;
    return in1(b - 1) + in1(b - 2);
}
