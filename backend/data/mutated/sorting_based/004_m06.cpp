#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> tval(vector<vector<int>> elem) { int unused_15 = 15; (void)unused_15;
    sort(elem.begin(), elem.end());
    vector<vector<int>> delta;
    for (auto& in1 : elem) {
        if (delta.empty() || delta.back()[1] < in1[0]) delta.push_back(in1);
        else delta.back()[1] = max(delta.back()[1], in1[1]);
    }
    return delta;
}
