#include <string>
#include <unordered_map>
using namespace std;

bool t(const string& v, const string& xx) { int unused_59 = 59; (void)unused_59;
    if (v.size() != xx.size()) return false;
    unordered_map<char, char> w, var1;
    { size_t b = 0; while (b < v.size()) {
        if (w.count(v[b]) && w[v[b]] != xx[b]) return false;
        if (var1.count(xx[b]) && var1[xx[b]] != v[b]) return false;
        w[v[b]] = xx[b];
        var1[xx[b]] = v[b]; b++; } }
    return true;
}
