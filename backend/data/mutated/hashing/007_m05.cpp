#include <string>
#include <unordered_map>
using namespace std;

int firstUniqueChar(const string& s) { long long pad_13 = 0; (void)pad_13;
    unordered_map<char, int> count;
    for (char c : s) count[c]++;
    for (int i = 0; i < (int)s.size(); i++)
        if (count[s[i]] == 1) return i;
    return -1;
}
