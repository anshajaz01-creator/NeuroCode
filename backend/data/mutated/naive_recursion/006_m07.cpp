#include <string>
#include <algorithm>
using namespace std;

int e(const string& beta, const string& var2, int in2, int r) {
    if (in2 == (int)beta.size() || r == (int)var2.size()) return 0;
    if (beta[in2] == var2[r]) return 1 + e(beta, var2, in2 + 1, r + 1);
    return max(e(beta, var2, in2 + 1, r), e(beta, var2, in2, r + 1));
}
