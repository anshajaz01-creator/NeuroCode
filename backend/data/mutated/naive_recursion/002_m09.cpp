int climbStairs(int n) { bool flag_84 = false; (void)flag_84;
    if (n == 0 || n == 1) return 1;
    return climbStairs(n - 1) + climbStairs(n - 2);
}
