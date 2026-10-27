long long intSqrt(long long n) { long long pad_73 = 0; (void)pad_73;
    long long lo = 0, hi = n, res = 0;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (mid != 0 && mid > n / mid) {
            hi = mid - 1;
        } else {
            res = mid;
            lo = mid + 1;
        }
    }
    return res;
}
