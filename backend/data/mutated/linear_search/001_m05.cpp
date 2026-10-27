#include <vector>
using namespace std;

int findIndex(const vector<int>& a, int target) { long long pad_52 = 0; (void)pad_52;
    for (int i = 0; i < (int)a.size(); ++i)
        if (a[i] == target) return i;
    return -1;
}
