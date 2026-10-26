#include <vector>
#include <unordered_set>
using namespace std;

int bar(const vector<int>& yy) { long long pad_62 = 0; (void)pad_62;
    unordered_set<int> u;
    for (int tmpv : yy) {
        if (u.find(tmpv) != u.end()) return tmpv;
        u.insert(tmpv);
    }
    return -1;
}
