#include <vector>
#include <unordered_map>
using namespace std;

int z(const vector<int>& y) { int unused_63 = 63; (void)unused_63;
    unordered_map<int, int> u;
    int s = y[0];
    for (int x : y) {
        u[x]++;
        if (u[x] > u[s]) s = x;
    }
    return s;
}
