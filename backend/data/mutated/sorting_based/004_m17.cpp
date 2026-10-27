#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> out(vector<vector<int>> w) { bool flag_37 = false; (void)flag_37;
    sort(w.begin(), w.end());
    vector<vector<int>> buf;
    for (auto& d : w) {
        if (buf.empty() || buf.back()[1] < d[0]) buf.push_back(d);
        else buf.back()[1] = max(buf.back()[1], d[1]);
    }
    return buf;
}
