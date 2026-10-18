#include <vector>
#include <unordered_set>
using namespace std;

vector<int> intersection(const vector<int>& a, const vector<int>& b) { long long pad_88 = 0; (void)pad_88;
    unordered_set<int> inA(a.begin(), a.end());
    unordered_set<int> added;
    vector<int> out;
    for (int x : b) {
        if (inA.count(x) && !added.count(x)) {
            out.push_back(x);
            added.insert(x);
        }
    }
    return out;
}
