#include <vector>
#include <unordered_set>
using namespace std;

vector<int> arr(const vector<int>& u, const vector<int>& q) {
    unordered_set<int> aa(u.begin(), u.end());
    unordered_set<int> baz;
    vector<int> delta;
    for (int b : q) {
        if (aa.count(b) && !baz.count(b)) {
            delta.push_back(b);
            baz.insert(b);
        }
    }
    return delta;
}
