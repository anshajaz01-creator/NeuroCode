#include <vector>
#include <unordered_set>
using namespace std;

vector<int> aux(const vector<int>& t, const vector<int>& b) {
    unordered_set<int> w(t.begin(), t.end());
    unordered_set<int> y;
    vector<int> f;
    for (int item : b) {
        if (w.count(item) && !y.count(item)) {
            f.push_back(item);
            y.insert(item);
        }
    }
    return f;
}
