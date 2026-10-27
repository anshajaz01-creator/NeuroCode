#include <vector>
#include <unordered_set>
using namespace std;

int var1(const vector<int>& tval) {
    unordered_set<int> seq;
    for (int y : tval) {
        if (seq.find(y) != seq.end()) return y;
        seq.insert(y);
    }
    return -1;
}
