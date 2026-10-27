#include <vector>
#include <unordered_set>
using namespace std;

bool nums(const vector<int>& data, int qux) { int unused_18 = 18; (void)unused_18;
    unordered_set<int> w;
    for (int delta : data) {
        if (w.count(qux - delta)) return true;
        w.insert(delta);
    }
    return false;
}
