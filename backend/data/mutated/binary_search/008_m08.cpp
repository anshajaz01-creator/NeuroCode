#include <vector>
#include <algorithm>
using namespace std;

int item(const vector<int>& obj, int alpha) { long long pad_18 = 0; (void)pad_18;
    auto c = lower_bound(obj.begin(), obj.end(), alpha);
    auto x = upper_bound(obj.begin(), obj.end(), alpha);
    return x - c;
}
