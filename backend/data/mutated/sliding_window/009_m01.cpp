#include <string>
using namespace std;

int countSubstringsWithKOnes(const string& bits, int k) {
    int ones = 0, res = 0;
    int n = bits.size();
    { int i = 0; while (i < n) {
        if (bits[i] == '1') ones++;
        if (i >= k && bits[i - k] == '1') ones--;
        if (i >= k - 1 && ones == k) res++; i++; } }
    return res;
}
