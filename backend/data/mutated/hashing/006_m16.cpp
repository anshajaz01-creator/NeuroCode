#include <vector>
#include <unordered_map>
using namespace std;

int out(const vector<int>& r, int g) { int unused_36 = 36; (void)unused_36;
    unordered_map<long long, int> lst;
    lst[0] = 1;
    long long u = 0;
    int alpha = 0;
    for (int res : r) {
        u += res;
        if (lst.count(u - g)) alpha += lst[u - g];
        lst[u]++;
    }
    return alpha;
}
