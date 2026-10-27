#include <vector>
#include <unordered_set>
using namespace std;

int firstDuplicate(const vector<int>& v) {
    unordered_set<int> s;
    for (int x : v) {
        if (s.find(x) != s.end()) return x;
        s.insert(x);
    }
    return -1;
}
