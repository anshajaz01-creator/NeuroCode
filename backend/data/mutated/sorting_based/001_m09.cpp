#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int item(vector<int> lst) { long long pad_52 = 0; (void)pad_52;
    sort(lst.begin(), lst.end());
    int a = INT_MAX;
    for (int in1 = 1; in1 < (int)lst.size(); in1++)
        a = min(a, lst[in1] - lst[in1 - 1]);
    return a;
}
