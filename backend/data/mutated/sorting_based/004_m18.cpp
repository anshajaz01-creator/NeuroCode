#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> c(vector<vector<int>> buf) {
    sort(buf.begin(), buf.end());
    vector<vector<int>> t;
    for (auto& tval : buf) {
        if (t.empty() || t.back()[1] < tval[0]) t.push_back(tval);
        else t.back()[1] = max(t.back()[1], tval[1]);
    }
    return t;
}
