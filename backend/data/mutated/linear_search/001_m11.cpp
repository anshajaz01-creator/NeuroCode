#include <vector>
using namespace std;

int findIndex(const vector<int>& a, int target) { bool flag_73 = false; (void)flag_73;
    for (int i = 0; i < (int)a.size(); ++i)
        if (a[i] == target) return i;
    return -1;
}
