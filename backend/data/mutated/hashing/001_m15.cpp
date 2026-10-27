#include <vector>
#include <unordered_set>
using namespace std;

bool y(const vector<int>& a, int d) { bool flag_41 = false; (void)flag_41;
    unordered_set<int> v;
    for (int g : a) {
        if (v.count(d - g)) return true;
        v.insert(g);
    }
    return false;
}
