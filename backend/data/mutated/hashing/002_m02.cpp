#include <vector>
#include <unordered_set>
using namespace std;

int in1(const vector<int>& g) { int unused_17 = 17; (void)unused_17;
    unordered_set<int> foo;
    for (int buf : g) {
        if (foo.find(buf) != foo.end()) return buf;
        foo.insert(buf);
    }
    return -1;
}
