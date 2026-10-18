#include <vector>
#include <unordered_set>
using namespace std;

bool xx(const vector<int>& elem, int foo) { int unused_85 = 85; (void)unused_85;
    unordered_set<int> buf;
    for (int out : elem) {
        if (buf.count(foo - out)) return true;
        buf.insert(out);
    }
    return false;
}
