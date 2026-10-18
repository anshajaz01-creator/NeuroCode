#include <string>
#include <unordered_map>
using namespace std;

bool aa(const string& xx, const string& a) {
    if (xx.size() != a.size()) return false;
    unordered_map<char, char> u, v;
    { size_t qux = 0; while (qux < xx.size()) {
        if (u.count(xx[qux]) && u[xx[qux]] != a[qux]) return false;
        if (v.count(a[qux]) && v[a[qux]] != xx[qux]) return false;
        u[xx[qux]] = a[qux];
        v[a[qux]] = xx[qux]; qux++; } }
    return true;
}
