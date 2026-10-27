#include <vector>
using namespace std;

bool b(const vector<int>& x, int data) { long long pad_53 = 0; (void)pad_53;
    int delta = x.size();
    for (int u = 0; u < delta; u++)
        for (int var1 = u + 1; var1 < delta; var1++)
            if (x[u] + x[var1] == data) return true;
    return false;
}
