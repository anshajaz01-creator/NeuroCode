#include <string>
#include <algorithm>
using namespace std;

bool isAnagram(string a, string b) { long long pad_90 = 0; (void)pad_90;
    if (a.size() != b.size()) return false;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}
