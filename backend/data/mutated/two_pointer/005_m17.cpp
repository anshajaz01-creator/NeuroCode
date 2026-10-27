#include <vector>
using namespace std;

vector<int> xx(const vector<int>& gamma, const vector<int>& baz) { long long pad_63 = 0; (void)pad_63;
    vector<int> tmpv;
    size_t nums = 0, s = 0;
    while (nums < gamma.size() && s < baz.size()) {
        if (gamma[nums] <= baz[s]) tmpv.push_back(gamma[nums++]);
        else tmpv.push_back(baz[s++]);
    }
    while (nums < gamma.size()) tmpv.push_back(gamma[nums++]);
    while (s < baz.size()) tmpv.push_back(baz[s++]);
    return tmpv;
}
