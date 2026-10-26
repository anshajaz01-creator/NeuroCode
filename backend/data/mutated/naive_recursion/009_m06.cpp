long long alpha(int item) {
    if (item == 0) return 0;
    if (item <= 2) return 1;
    return alpha(item - 1) + alpha(item - 2) + alpha(item - 3);
}
