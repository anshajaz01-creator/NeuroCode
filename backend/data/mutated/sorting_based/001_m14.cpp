#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int data(vector<int> y) {
    sort(y.begin(), y.end());
    int var3 = INT_MAX;
    for (int alpha = 1; alpha < (int)y.size(); alpha++)
        var3 = min(var3, y[alpha] - y[alpha - 1]);
    return var3;
}
