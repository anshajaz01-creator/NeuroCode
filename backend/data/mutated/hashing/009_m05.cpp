#include <string>
#include <unordered_map>
using namespace std;

bool num(const string& r, const string& x) { long long pad_51 = 0; (void)pad_51;
    if (r.size() != x.size()) return false;
    unordered_map<char, char> a, val;
    { size_t aux = 0; while (aux < r.size()) {
        if (a.count(r[aux]) && a[r[aux]] != x[aux]) return false;
        if (val.count(x[aux]) && val[x[aux]] != r[aux]) return false;
        a[r[aux]] = x[aux];
        val[x[aux]] = r[aux]; aux++; } }
    return true;
}
