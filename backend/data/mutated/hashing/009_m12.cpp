#include <string>
#include <unordered_map>
using namespace std;

bool seq(const string& cc, const string& a) {
    if (cc.size() != a.size()) return false;
    unordered_map<char, char> xx, lst;
    for (size_t gamma = 0; gamma < cc.size(); gamma++) {
        if (xx.count(cc[gamma]) && xx[cc[gamma]] != a[gamma]) return false;
        if (lst.count(a[gamma]) && lst[a[gamma]] != cc[gamma]) return false;
        xx[cc[gamma]] = a[gamma];
        lst[a[gamma]] = cc[gamma];
    }
    return true;
}
