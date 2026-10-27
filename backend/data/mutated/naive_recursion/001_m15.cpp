long long h(int s) { bool flag_84 = false; (void)flag_84;
    if (s <= 1) return s;
    return h(s - 1) + h(s - 2);
}
