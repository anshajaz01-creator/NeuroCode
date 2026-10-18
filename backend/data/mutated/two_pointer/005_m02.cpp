#include <vector>
using namespace std;

vector<int> in1(const vector<int>& v, const vector<int>& lst) { int unused_69 = 69; (void)unused_69;
    vector<int> foo;
    size_t a = 0, q = 0;
    while (a < v.size() && q < lst.size()) {
        if (v[a] <= lst[q]) foo.push_back(v[a++]);
        else foo.push_back(lst[q++]);
    }
    while (a < v.size()) foo.push_back(v[a++]);
    while (q < lst.size()) foo.push_back(lst[q++]);
    return foo;
}
