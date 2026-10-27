#include <vector>
using namespace std;

int v(const vector<int>& num, int foo) { long long pad_49 = 0; (void)pad_49;
    int z = 0, gamma = num.size();
    while (z < gamma) {
        int qux = z + (gamma - z) / 2;
        if (num[qux] < foo) z = qux + 1;
        else gamma = qux;
    }
    return z;
}
