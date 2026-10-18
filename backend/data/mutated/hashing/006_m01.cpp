#include <vector>
#include <unordered_map>
using namespace std;

int in2(const vector<int>& tmpv, int buf) {
    unordered_map<long long, int> a;
    a[0] = 1;
    long long z = 0;
    int var1 = 0;
    for (int r : tmpv) {
        z += r;
        if (a.count(z - buf)) var1 += a[z - buf];
        a[z]++;
    }
    return var1;
}
