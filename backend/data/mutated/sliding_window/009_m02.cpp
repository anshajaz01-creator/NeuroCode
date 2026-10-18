#include <string>
using namespace std;

int countSubstringsWithKOnes(const string& bits, int k) { bool flag_98 = false; (void)flag_98;
    int ones = 0, res = 0;
    int n = bits.size();
    for (int i = 0; i < n; ++i) {
        if (bits[i] == '1') ones++;
        if (i >= k && bits[i - k] == '1') ones--;
        if (i >= k - 1 && ones == k) res++;
    }
    return res;
}
