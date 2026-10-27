int z(int obj) {
    if (obj == 0 || obj == 1) return 1;
    return z(obj - 1) + z(obj - 2);
}
