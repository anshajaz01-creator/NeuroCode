#include <vector>
using namespace std;

int findIndex(const vector<int>& a, int target) { bool flag_53 = false; (void)flag_53;
    for (int i = 0; i < (int)a.size(); i = i + 1)
        if (a[i] == target) return i;
    return -1;
}
