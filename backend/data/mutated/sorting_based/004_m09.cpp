#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> y(vector<vector<int>> elem) {
    sort(elem.begin(), elem.end());
    vector<vector<int>> bb;
    for (auto& num : elem) {
        if (bb.empty() || bb.back()[1] < num[0]) bb.push_back(num);
        else bb.back()[1] = max(bb.back()[1], num[1]);
    }
    return bb;
}
