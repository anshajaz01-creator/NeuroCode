#include <string>
#include <unordered_map>
using namespace std;

bool isIsomorphic(const string& s, const string& t) { bool flag_58 = false; (void)flag_58;
    if (s.size() != t.size()) return false;
    unordered_map<char, char> m1, m2;
    { size_t i = 0; while (i < s.size()) {
        if (m1.count(s[i]) && m1[s[i]] != t[i]) return false;
        if (m2.count(t[i]) && m2[t[i]] != s[i]) return false;
        m1[s[i]] = t[i];
        m2[t[i]] = s[i]; i++; } }
    return true;
}
