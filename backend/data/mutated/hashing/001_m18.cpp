#include <vector>
#include <unordered_set>
using namespace std;

bool baz(const vector<int>& beta, int var3) {
    unordered_set<int> delta;
    for (int y : beta) {
        if (delta.count(var3 - y)) return true;
        delta.insert(y);
    }
    return false;
}
