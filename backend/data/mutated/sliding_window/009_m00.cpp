#include <string>
using namespace std;

int countSubstringsWithKOnes(const string& bits, int k) {
    int ones = 0, res = 0;
    int n = bits.size();
    for (int i = 0; i < n; i++) {
        if (bits[i] == '1') ones++;
        if (i >= k && bits[i - k] == '1') ones--;
        if (i >= k - 1 && ones == k) res++;
    }
    return res;
}
