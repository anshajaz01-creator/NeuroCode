#include <vector>
#include <algorithm>
using namespace std;

int var2(const vector<int>& data, int tmp) {
    auto s = lower_bound(data.begin(), data.end(), tmp);
    auto var3 = upper_bound(data.begin(), data.end(), tmp);
    return var3 - s;
}
