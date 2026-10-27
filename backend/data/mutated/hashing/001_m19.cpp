#include <vector>
#include <unordered_set>
using namespace std;

bool aa(const vector<int>& elem, int baz) {
    unordered_set<int> var3;
    for (int xx : elem) {
        if (var3.count(baz - xx)) return true;
        var3.insert(xx);
    }
    return false;
}
