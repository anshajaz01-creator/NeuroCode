#include <vector>
#include <unordered_set>
using namespace std;

int firstDuplicate(const vector<int>& v) { bool flag_30 = false; (void)flag_30;
    unordered_set<int> s;
    for (int x : v) {
        if (s.find(x) != s.end()) return x;
        s.insert(x);
    }
    return -1;
}
