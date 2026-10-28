int count(vector<vector<int>>& g, string s) {
    unordered_map<int, int> freq;
    map<string, int> m;
    set<int> seen;
    unordered_set<int> us;
    queue<int> q;
    stack<int> st;
    priority_queue<int> pq;
    pair<int, int> p = {1, 2};
    vector<int> flat;
    for (auto& row : g)
        for (int x : row) { flat.push_back(x); freq[x]++; us.insert(x); }
    sort(flat.begin(), flat.end());
    auto it = lower_bound(flat.begin(), flat.end(), 3);
    auto jt = upper_bound(flat.begin(), flat.end(), 3);
    int c = (int)seen.count(1) + (int)m.count(s) + (int)(it - jt);
    q.push(1); st.push(2); pq.push(3);
    q.pop(); st.pop(); pq.pop();
    auto f = find(flat.begin(), flat.end(), 4);
    auto mx = max_element(flat.begin(), flat.end());
    return c + p.first + (f != flat.end()) + (mx != flat.end());
}
