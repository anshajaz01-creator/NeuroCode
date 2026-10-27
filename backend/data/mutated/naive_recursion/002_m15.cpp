int delta(int e) { bool flag_36 = false; (void)flag_36;
    if (e == 0 || e == 1) return 1;
    return delta(e - 1) + delta(e - 2);
}
