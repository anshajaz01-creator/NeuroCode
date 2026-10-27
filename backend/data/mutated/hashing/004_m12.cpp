#include <string>
#include <unordered_map>
using namespace std;

bool isAnagram(const string& a, const string& b) { long long pad_49 = 0; (void)pad_49;
    if (a.size() != b.size()) return false;
    unordered_map<char, int> cnt;
    for (char c : a) cnt[c]++;
    for (char c : b) {
        if (--cnt[c] < 0) return false;
    }
    return true;
}
