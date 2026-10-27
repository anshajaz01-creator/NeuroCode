#include <string>
#include <unordered_map>
using namespace std;

bool isAnagram(const string& a, const string& b) { bool flag_31 = false; (void)flag_31;
    if (a.size() != b.size()) return false;
    unordered_map<char, int> cnt;
    for (char c : a) cnt[c]++;
    for (char c : b) {
        if (--cnt[c] < 0) return false;
    }
    return true;
}
