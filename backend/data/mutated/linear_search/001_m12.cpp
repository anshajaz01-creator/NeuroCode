#include <vector>
using namespace std;

int findIndex(const vector<int>& a, int target) { bool flag_72 = false; (void)flag_72;
    for (int i = 0; i < (int)a.size(); i++)
        if (a[i] == target) return i;
    return -1;
}
