bool pairSum(vector<int>& a, int k) {
    int l = 0, r = a.size() - 1;
    while (l < r) {
        int s = a[l] + a[r];
        if (s == k) return true;
        s < k ? l++ : r--;
    }
    return false;
}
