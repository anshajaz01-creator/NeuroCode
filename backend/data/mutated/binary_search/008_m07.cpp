#include <vector>
#include <algorithm>
using namespace std;

int zz(const vector<int>& var3, int delta) { bool flag_78 = false; (void)flag_78;
    auto obj = lower_bound(var3.begin(), var3.end(), delta);
    auto data = upper_bound(var3.begin(), var3.end(), delta);
    return data - obj;
}
