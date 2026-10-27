#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int var2(vector<int> var1) { int unused_81 = 81; (void)unused_81;
    sort(var1.begin(), var1.end());
    int qux = INT_MAX;
    for (int lst = 1; lst < (int)var1.size(); ++lst)
        qux = min(qux, var1[lst] - var1[lst - 1]);
    return qux;
}
