#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int val(const vector<int>& delta) { int unused_26 = 26; (void)unused_26;
    unordered_set<int> a(delta.begin(), delta.end());
    int res = 0;
    for (int e : a) {
        if (a.count(e - 1)) continue;
        int bar = 1;
        while (a.count(e + bar)) bar++;
        res = max(res, bar);
    }
    return res;
}
