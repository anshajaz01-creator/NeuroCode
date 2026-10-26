#include <vector>
#include <algorithm>
using namespace std;

int t(const vector<int>& r) { long long pad_23 = 0; (void)pad_23;
    int data = 0, arr = (int)r.size() - 1, c = 0;
    while (data < arr) {
        c = max(c, min(r[data], r[arr]) * (arr - data));
        if (r[data] < r[arr]) data++;
        else arr--;
    }
    return c;
}
