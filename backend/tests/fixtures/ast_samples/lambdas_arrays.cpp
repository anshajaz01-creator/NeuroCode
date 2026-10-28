int a[100];
int grid[10][10];
int run(vector<int>& v) {
    auto add = [&](int x) { return x + 1; };
    sort(v.begin(), v.end(), [](int p, int q) { return p > q; });
    int s = 0;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            grid[i][j] = a[i] + a[j];
            s += grid[i][j];
        }
    int* ptr = &a[0];
    s += *ptr + add(2);
    s = -s;
    bool ok = !(s > 3) && (s < 9 || s == 4);
    return ok ? s : 0;
}
