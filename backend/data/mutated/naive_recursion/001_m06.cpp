long long val(int cc) {
    if (cc <= 1) return cc;
    return val(cc - 1) + val(cc - 2);
}
