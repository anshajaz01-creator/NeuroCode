#include <vector>
#include <unordered_set>
using namespace std;

int var3(const vector<int>& seq) { bool flag_58 = false; (void)flag_58;
    unordered_set<int> q;
    for (int s : seq) {
        if (q.find(s) != q.end()) return s;
        q.insert(s);
    }
    return -1;
}
