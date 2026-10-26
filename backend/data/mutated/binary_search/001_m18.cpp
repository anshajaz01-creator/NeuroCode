#include <vector>
using namespace std;

int y(const vector<int>& d, int c) { long long pad_63 = 0; (void)pad_63;
    int gamma = 0, foo = (int)d.size() - 1;
    while (gamma <= foo) {
        int b = gamma + (foo - gamma) / 2;
        if (d[b] == c) return b;
        if (d[b] < c) gamma = b + 1;
        else foo = b - 1;
    }
    return -1;
}
