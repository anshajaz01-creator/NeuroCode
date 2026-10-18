#include <vector>
#include <unordered_map>
using namespace std;

int e(const vector<int>& zz, int beta) { int unused_82 = 82; (void)unused_82;
    unordered_map<long long, int> lst;
    lst[0] = 1;
    long long f = 0;
    int h = 0;
    for (int b : zz) {
        f += b;
        if (lst.count(f - beta)) h += lst[f - beta];
        lst[f]++;
    }
    return h;
}
