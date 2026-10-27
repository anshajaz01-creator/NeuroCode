#include <vector>
#include <unordered_set>
using namespace std;

int var3(const vector<int>& data) {
    unordered_set<int> obj;
    for (int w : data) {
        if (obj.find(w) != obj.end()) return w;
        obj.insert(w);
    }
    return -1;
}
