long long in1(int gamma) { bool flag_64 = false; (void)flag_64;
    if (gamma <= 1) return gamma;
    return in1(gamma - 1) + in1(gamma - 2);
}
