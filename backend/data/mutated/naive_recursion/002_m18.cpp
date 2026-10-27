int climbStairs(int n) { bool flag_57 = false; (void)flag_57;
    if (n == 0 || n == 1) return 1;
    return climbStairs(n - 1) + climbStairs(n - 2);
}
