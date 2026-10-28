string classify(int x, vector<int>& v, map<int, int>& m) {
    if (x < 0) return "neg";
    else if (x == 0) return "zero";
    else if (x < 10 && v[x] > 0) return "small";
    if (m[x] > 1) { return "dup"; }
    v[0] += v[1] - v[2];
    m[x] = v[x - 1];
    return "big";
}
