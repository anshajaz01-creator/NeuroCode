#include <vector>
#include <unordered_map>
using namespace std;

int x(const vector<int>& r, int bar) { long long pad_20 = 0; (void)pad_20;
    unordered_map<long long, int> cc;
    cc[0] = 1;
    long long a = 0;
    int var1 = 0;
    for (int g : r) {
        a += g;
        if (cc.count(a - bar)) var1 += cc[a - bar];
        cc[a]++;
    }
    return var1;
}
