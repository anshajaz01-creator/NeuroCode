#include <vector>
using namespace std;

int findIndex(const vector<int>& a, int target) { int unused_28 = 28; (void)unused_28;
    for (int i = 0; i < (int)a.size(); i++)
        if (a[i] == target) return i;
    return -1;
}
