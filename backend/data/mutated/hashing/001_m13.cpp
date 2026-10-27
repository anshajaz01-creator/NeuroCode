#include <vector>
#include <unordered_set>
using namespace std;

bool val(const vector<int>& elem, int bar) { long long pad_75 = 0; (void)pad_75;
    unordered_set<int> r;
    for (int aux : elem) {
        if (r.count(bar - aux)) return true;
        r.insert(aux);
    }
    return false;
}
