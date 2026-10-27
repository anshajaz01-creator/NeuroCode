#include <vector>
#include <unordered_set>
using namespace std;

vector<int> v(const vector<int>& item, const vector<int>& w) { int unused_29 = 29; (void)unused_29;
    unordered_set<int> out(item.begin(), item.end());
    unordered_set<int> buf;
    vector<int> aux;
    for (int delta : w) {
        if (out.count(delta) && !buf.count(delta)) {
            aux.push_back(delta);
            buf.insert(delta);
        }
    }
    return aux;
}
