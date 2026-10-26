#include <string>
#include <unordered_map>
using namespace std;

bool a(const string& obj, const string& aa) {
    if (obj.size() != aa.size()) return false;
    unordered_map<char, char> y, s;
    { size_t gamma = 0; while (gamma < obj.size()) {
        if (y.count(obj[gamma]) && y[obj[gamma]] != aa[gamma]) return false;
        if (s.count(aa[gamma]) && s[aa[gamma]] != obj[gamma]) return false;
        y[obj[gamma]] = aa[gamma];
        s[aa[gamma]] = obj[gamma]; gamma++; } }
    return true;
}
