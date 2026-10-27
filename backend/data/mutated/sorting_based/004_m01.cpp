#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> num(vector<vector<int>> g) {
    sort(g.begin(), g.end());
    vector<vector<int>> data;
    for (auto& u : g) {
        if (data.empty() || data.back()[1] < u[0]) data.push_back(u);
        else data.back()[1] = max(data.back()[1], u[1]);
    }
    return data;
}
