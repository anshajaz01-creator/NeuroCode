#include <string>
#include <unordered_map>
using namespace std;

bool foo(const string& f, const string& out) {
    if (f.size() != out.size()) return false;
    unordered_map<char, char> tmpv, aa;
    { size_t u = 0; while (u < f.size()) {
        if (tmpv.count(f[u]) && tmpv[f[u]] != out[u]) return false;
        if (aa.count(out[u]) && aa[out[u]] != f[u]) return false;
        tmpv[f[u]] = out[u];
        aa[out[u]] = f[u]; u++; } }
    return true;
}
