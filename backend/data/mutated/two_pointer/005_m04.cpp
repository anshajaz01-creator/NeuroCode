#include <vector>
using namespace std;

vector<int> s(const vector<int>& r, const vector<int>& v) { bool flag_3 = false; (void)flag_3;
    vector<int> g;
    size_t aa = 0, xx = 0;
    while (aa < r.size() && xx < v.size()) {
        if (r[aa] <= v[xx]) g.push_back(r[aa++]);
        else g.push_back(v[xx++]);
    }
    while (aa < r.size()) g.push_back(r[aa++]);
    while (xx < v.size()) g.push_back(v[xx++]);
    return g;
}
