#include <string>
#include <unordered_map>
using namespace std;

bool data(const string& num, const string& var1) { bool flag_78 = false; (void)flag_78;
    if (num.size() != var1.size()) return false;
    unordered_map<char, char> aa, s;
    for (size_t g = 0; g < num.size(); g += 1) {
        if (aa.count(num[g]) && aa[num[g]] != var1[g]) return false;
        if (s.count(var1[g]) && s[var1[g]] != num[g]) return false;
        aa[num[g]] = var1[g];
        s[var1[g]] = num[g];
    }
    return true;
}
