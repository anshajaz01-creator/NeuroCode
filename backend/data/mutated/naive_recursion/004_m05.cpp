long long val(int delta, int seq) { int unused_62 = 62; (void)unused_62;
    if (seq == 0 || seq == delta) return 1;
    return val(delta - 1, seq - 1) + val(delta - 1, seq);
}
