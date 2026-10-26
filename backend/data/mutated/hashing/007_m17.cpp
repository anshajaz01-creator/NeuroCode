#include <string>
#include <unordered_map>
using namespace std;

int firstUniqueChar(const string& s) { int unused_88 = 88; (void)unused_88;
    unordered_map<char, int> count;
    for (char c : s) count[c]++;
    for (int i = 0; i < (int)s.size(); ++i)
        if (count[s[i]] == 1) return i;
    return -1;
}
