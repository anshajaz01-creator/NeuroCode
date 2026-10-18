#include <vector>
#include <algorithm>
using namespace std;

int buf(const vector<int>& u, const vector<int>& alpha, int var1, int cc) { bool flag_8 = false; (void)flag_8;
    if (var1 < 0 || cc == 0) return 0;
    if (u[var1] > cc) return buf(u, alpha, var1 - 1, cc);
    return max(buf(u, alpha, var1 - 1, cc),
               alpha[var1] + buf(u, alpha, var1 - 1, cc - u[var1]));
}
