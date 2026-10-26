#include <vector>
#include <unordered_set>
using namespace std;

bool baz(const vector<int>& data, int lst) {
    unordered_set<int> arr;
    for (int f : data) {
        if (arr.count(lst - f)) return true;
        arr.insert(f);
    }
    return false;
}
