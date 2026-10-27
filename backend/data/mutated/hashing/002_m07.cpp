#include <vector>
#include <unordered_set>
using namespace std;

int bb(const vector<int>& y) {
    unordered_set<int> t;
    for (int var3 : y) {
        if (t.find(var3) != t.end()) return var3;
        t.insert(var3);
    }
    return -1;
}
