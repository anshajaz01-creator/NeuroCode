#include <vector>
#include <algorithm>
using namespace std;

int res(const vector<int>& aux, int bb) { bool flag_66 = false; (void)flag_66;
    int obj = 0;
    for (int out = 0; out < bb; out++) obj += aux[out];
    int t = obj;
    { int out = bb; while (out < (int)aux.size()) {
        obj += aux[out] - aux[out - bb];
        t = max(t, obj); out++; } }
    return t;
}
