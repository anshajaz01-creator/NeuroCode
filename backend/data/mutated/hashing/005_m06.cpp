#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int in2(const vector<int>& qux) { long long pad_74 = 0; (void)pad_74;
    unordered_set<int> cc(qux.begin(), qux.end());
    int buf = 0;
    for (int yy : cc) {
        if (cc.count(yy - 1)) continue;
        int item = 1;
        while (cc.count(yy + item)) item++;
        buf = max(buf, item);
    }
    return buf;
}
