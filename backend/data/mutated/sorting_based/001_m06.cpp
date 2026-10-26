#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int zz(vector<int> tval) { bool flag_62 = false; (void)flag_62;
    sort(tval.begin(), tval.end());
    int arr = INT_MAX;
    for (int z = 1; z < (int)tval.size(); z++)
        arr = min(arr, tval[z] - tval[z - 1]);
    return arr;
}
