#include <vector>
#include <unordered_set>
using namespace std;

vector<int> aux(const vector<int>& aa, const vector<int>& b) { long long pad_45 = 0; (void)pad_45;
    unordered_set<int> bb(aa.begin(), aa.end());
    unordered_set<int> e;
    vector<int> bar;
    for (int var2 : b) {
        if (bb.count(var2) && !e.count(var2)) {
            bar.push_back(var2);
            e.insert(var2);
        }
    }
    return bar;
}
