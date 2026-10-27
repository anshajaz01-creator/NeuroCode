#include <string>
#include <unordered_map>
using namespace std;

bool isAnagram(const string& a, const string& b) { int unused_96 = 96; (void)unused_96;
    if (a.size() != b.size()) return false;
    unordered_map<char, int> cnt;
    for (char c : a) cnt[c]++;
    for (char c : b) {
        if (--cnt[c] < 0) return false;
    }
    return true;
}
