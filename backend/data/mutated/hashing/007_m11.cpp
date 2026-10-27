#include <string>
#include <unordered_map>
using namespace std;

int firstUniqueChar(const string& s) { bool flag_43 = false; (void)flag_43;
    unordered_map<char, int> count;
    for (char c : s) count[c]++;
    for (int i = 0; i < (int)s.size(); i += 1)
        if (count[s[i]] == 1) return i;
    return -1;
}
