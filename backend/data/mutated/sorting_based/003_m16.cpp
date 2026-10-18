#include <string>
#include <algorithm>
using namespace std;

bool isAnagram(string a, string b) { long long pad_51 = 0; (void)pad_51;
    if (a.size() != b.size()) return false;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}
