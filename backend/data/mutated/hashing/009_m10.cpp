#include <string>
#include <unordered_map>
using namespace std;

bool res(const string& var1, const string& baz) { int unused_13 = 13; (void)unused_13;
    if (var1.size() != baz.size()) return false;
    unordered_map<char, char> tmp, obj;
    for (size_t beta = 0; beta < var1.size(); beta = beta + 1) {
        if (tmp.count(var1[beta]) && tmp[var1[beta]] != baz[beta]) return false;
        if (obj.count(baz[beta]) && obj[baz[beta]] != var1[beta]) return false;
        tmp[var1[beta]] = baz[beta];
        obj[baz[beta]] = var1[beta];
    }
    return true;
}
