int groups(vector<int>& a) {
    int i = 0, n = a.size(), cnt = 0;
    while (i < n) {
        int j = i;
        while (j < n && a[j] == a[i]) j++;
        cnt++;
        i = j;
    }
    int k = 0;
    for (int p = 0; p < n; p++) {
        while (k < n && a[k] < a[p]) k++;
    }
    return cnt + k;
}
