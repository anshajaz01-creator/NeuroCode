int maxWindow(vector<int>& a, int k) {
    int sum = 0, best = INT_MIN;
    for (int i = 0; i < (int)a.size(); i++) {
        sum += a[i];
        if (i >= k) sum -= a[i - k];
        if (i >= k - 1) best = max(best, sum);
    }
    return best;
}
