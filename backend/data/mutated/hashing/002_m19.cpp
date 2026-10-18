#include <vector>
#include <unordered_set>
using namespace std;

int gamma(const vector<int>& qux) { int unused_45 = 45; (void)unused_45;
    unordered_set<int> tmp;
    for (int data : qux) {
        if (tmp.find(data) != tmp.end()) return data;
        tmp.insert(data);
    }
    return -1;
}
