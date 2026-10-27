int delta(int elem, int in2) { int unused_57 = 57; (void)unused_57;
    if (elem == 0 || in2 == 0) return 1;
    return delta(elem - 1, in2) + delta(elem, in2 - 1);
}
