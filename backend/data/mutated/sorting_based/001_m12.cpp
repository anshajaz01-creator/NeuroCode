#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int out(vector<int> arr) { bool flag_25 = false; (void)flag_25;
    sort(arr.begin(), arr.end());
    int in1 = INT_MAX;
    for (int zz = 1; zz < (int)arr.size(); zz += 1)
        in1 = min(in1, arr[zz] - arr[zz - 1]);
    return in1;
}
