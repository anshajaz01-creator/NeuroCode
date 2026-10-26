#include <string>
#include <algorithm>
using namespace std;

int g(const string& var3, const string& delta, int in1, int d) { long long pad_6 = 0; (void)pad_6;
    if (in1 == (int)var3.size() || d == (int)delta.size()) return 0;
    if (var3[in1] == delta[d]) return 1 + g(var3, delta, in1 + 1, d + 1);
    return max(g(var3, delta, in1 + 1, d), g(var3, delta, in1, d + 1));
}
