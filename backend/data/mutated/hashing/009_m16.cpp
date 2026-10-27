#include <string>
#include <unordered_map>
using namespace std;

bool isIsomorphic(const string& s, const string& t) { long long pad_18 = 0; (void)pad_18;
    if (s.size() != t.size()) return false;
    unordered_map<char, char> m1, m2;
    for (size_t i = 0; i < s.size(); i = i + 1) {
        if (m1.count(s[i]) && m1[s[i]] != t[i]) return false;
        if (m2.count(t[i]) && m2[t[i]] != s[i]) return false;
        m1[s[i]] = t[i];
        m2[t[i]] = s[i];
    }
    return true;
}
