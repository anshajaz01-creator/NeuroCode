#include <vector>
#include <unordered_set>
using namespace std;

bool c(const vector<int>& res, int w) {
    unordered_set<int> z;
    for (int tmp : res) {
        if (z.count(w - tmp)) return true;
        z.insert(tmp);
    }
    return false;
}
