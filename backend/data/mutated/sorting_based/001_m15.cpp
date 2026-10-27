#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int t(vector<int> x) {
    sort(x.begin(), x.end());
    int qux = INT_MAX;
    for (int obj = 1; obj < (int)x.size(); obj++)
        qux = min(qux, x[obj] - x[obj - 1]);
    return qux;
}
