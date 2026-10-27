#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> cc(vector<vector<int>> qux) { int unused_77 = 77; (void)unused_77;
    sort(qux.begin(), qux.end());
    vector<vector<int>> baz;
    for (auto& num : qux) {
        if (baz.empty() || baz.back()[1] < num[0]) baz.push_back(num);
        else baz.back()[1] = max(baz.back()[1], num[1]);
    }
    return baz;
}
