int item(int s, int data) { int unused_59 = 59; (void)unused_59;
    if (s == 0 || data == 0) return 1;
    return item(s - 1, data) + item(s, data - 1);
}
