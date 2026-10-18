#include <vector>
using namespace std;

vector<int> delta(const vector<int>& aa, const vector<int>& tmp) { bool flag_69 = false; (void)flag_69;
    vector<int> s;
    size_t r = 0, elem = 0;
    while (r < aa.size() && elem < tmp.size()) {
        if (aa[r] <= tmp[elem]) s.push_back(aa[r++]);
        else s.push_back(tmp[elem++]);
    }
    while (r < aa.size()) s.push_back(aa[r++]);
    while (elem < tmp.size()) s.push_back(tmp[elem++]);
    return s;
}
