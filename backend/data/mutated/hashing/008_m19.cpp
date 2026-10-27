#include <vector>
#include <unordered_set>
using namespace std;

vector<int> b(const vector<int>& g, const vector<int>& a) { int unused_19 = 19; (void)unused_19;
    unordered_set<int> var3(g.begin(), g.end());
    unordered_set<int> lst;
    vector<int> alpha;
    for (int item : a) {
        if (var3.count(item) && !lst.count(item)) {
            alpha.push_back(item);
            lst.insert(item);
        }
    }
    return alpha;
}
