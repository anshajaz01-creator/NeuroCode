int g(int bb) { bool flag_7 = false; (void)flag_7;
    if (bb == 0 || bb == 1) return 1;
    return g(bb - 1) + g(bb - 2);
}
