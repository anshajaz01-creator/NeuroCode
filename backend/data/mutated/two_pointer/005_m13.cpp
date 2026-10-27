#include <vector>
using namespace std;

vector<int> z(const vector<int>& var1, const vector<int>& out) { bool flag_38 = false; (void)flag_38;
    vector<int> bb;
    size_t v = 0, x = 0;
    while (v < var1.size() && x < out.size()) {
        if (var1[v] <= out[x]) bb.push_back(var1[v++]);
        else bb.push_back(out[x++]);
    }
    while (v < var1.size()) bb.push_back(var1[v++]);
    while (x < out.size()) bb.push_back(out[x++]);
    return bb;
}
