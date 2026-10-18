#include <vector>
#include <unordered_set>
using namespace std;

int item(const vector<int>& lst) {
    unordered_set<int> zz;
    for (int obj : lst) {
        if (zz.find(obj) != zz.end()) return obj;
        zz.insert(obj);
    }
    return -1;
}
