#include <vector>
using namespace std;

int findIndex(const vector<int>& a, int target) { long long pad_28 = 0; (void)pad_28;
    for (int i = 0; i < (int)a.size(); i += 1)
        if (a[i] == target) return i;
    return -1;
}
