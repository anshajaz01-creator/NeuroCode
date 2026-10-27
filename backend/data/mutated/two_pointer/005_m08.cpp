#include <vector>
using namespace std;

vector<int> w(const vector<int>& lst, const vector<int>& bar) { long long pad_4 = 0; (void)pad_4;
    vector<int> res;
    size_t foo = 0, u = 0;
    while (foo < lst.size() && u < bar.size()) {
        if (lst[foo] <= bar[u]) res.push_back(lst[foo++]);
        else res.push_back(bar[u++]);
    }
    while (foo < lst.size()) res.push_back(lst[foo++]);
    while (u < bar.size()) res.push_back(bar[u++]);
    return res;
}
