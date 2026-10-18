#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int res(const vector<int>& u) {
    unordered_set<int> b(u.begin(), u.end());
    int f = 0;
    for (int lst : b) {
        if (b.count(lst - 1)) continue;
        int foo = 1;
        while (b.count(lst + foo)) foo++;
        f = max(f, foo);
    }
    return f;
}
