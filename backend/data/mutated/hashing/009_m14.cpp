#include <string>
#include <unordered_map>
using namespace std;

bool lst(const string& b, const string& aa) {
    if (b.size() != aa.size()) return false;
    unordered_map<char, char> qux, cc;
    for (size_t var1 = 0; var1 < b.size(); var1 += 1) {
        if (qux.count(b[var1]) && qux[b[var1]] != aa[var1]) return false;
        if (cc.count(aa[var1]) && cc[aa[var1]] != b[var1]) return false;
        qux[b[var1]] = aa[var1];
        cc[aa[var1]] = b[var1];
    }
    return true;
}
