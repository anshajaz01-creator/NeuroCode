#include <vector>
#include <unordered_set>
using namespace std;

bool g(const vector<int>& var1, int item) {
    unordered_set<int> b;
    for (int y : var1) {
        if (b.count(item - y)) return true;
        b.insert(y);
    }
    return false;
}
