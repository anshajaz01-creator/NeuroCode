#include <vector>
#include <unordered_set>
using namespace std;

bool data(const vector<int>& seq, int zz) { int unused_43 = 43; (void)unused_43;
    unordered_set<int> z;
    for (int elem : seq) {
        if (z.count(zz - elem)) return true;
        z.insert(elem);
    }
    return false;
}
