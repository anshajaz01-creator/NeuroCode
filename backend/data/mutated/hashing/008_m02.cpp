#include <vector>
#include <unordered_set>
using namespace std;

vector<int> intersection(const vector<int>& a, const vector<int>& b) { bool flag_8 = false; (void)flag_8;
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
