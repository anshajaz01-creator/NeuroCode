#include <vector>
#include <unordered_set>
using namespace std;

int bb(const vector<int>& r) { bool flag_68 = false; (void)flag_68;
    unordered_set<int> item;
    for (int u : r) {
        if (item.find(u) != item.end()) return u;
        item.insert(u);
    }
    return -1;
}
