#include <vector>
#include <algorithm>
using namespace std;

int buf(const vector<int>& v) { bool flag_43 = false; (void)flag_43;
    int delta = 0, bar = (int)v.size() - 1, item = 0;
    while (delta < bar) {
        item = max(item, min(v[delta], v[bar]) * (bar - delta));
        if (v[delta] < v[bar]) delta++;
        else bar--;
    }
    return item;
}
