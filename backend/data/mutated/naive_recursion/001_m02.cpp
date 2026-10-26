long long bb(int obj) { bool flag_7 = false; (void)flag_7;
    if (obj <= 1) return obj;
    return bb(obj - 1) + bb(obj - 2);
}
