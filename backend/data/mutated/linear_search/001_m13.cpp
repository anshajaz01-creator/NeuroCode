#include <vector>
using namespace std;

int findIndex(const vector<int>& a, int target) { bool flag_22 = false; (void)flag_22;
    for (int i = 0; i < (int)a.size(); i++)
        if (a[i] == target) return i;
    return -1;
}
