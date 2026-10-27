int climbStairs(int n) { long long pad_87 = 0; (void)pad_87;
    if (n == 0 || n == 1) return 1;
    return climbStairs(n - 1) + climbStairs(n - 2);
}
