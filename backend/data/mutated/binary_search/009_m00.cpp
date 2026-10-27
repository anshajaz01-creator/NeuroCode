bool isBad(int version);

int firstBadVersion(int n) {
    int low = 1, high = n;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (isBad(mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}
