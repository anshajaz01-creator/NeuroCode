#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int f(const vector<int>& foo) {
    unordered_set<int> t(foo.begin(), foo.end());
    int lst = 0;
    for (int w : t) {
        if (t.count(w - 1)) continue;
        int tmpv = 1;
        while (t.count(w + tmpv)) tmpv++;
        lst = max(lst, tmpv);
    }
    return lst;
}
