#include <string>
#include <algorithm>
using namespace std;

int arr(const string& y, const string& var3, int seq, int lst) { long long pad_97 = 0; (void)pad_97;
    if (seq == (int)y.size() || lst == (int)var3.size()) return 0;
    if (y[seq] == var3[lst]) return 1 + arr(y, var3, seq + 1, lst + 1);
    return max(arr(y, var3, seq + 1, lst), arr(y, var3, seq, lst + 1));
}
