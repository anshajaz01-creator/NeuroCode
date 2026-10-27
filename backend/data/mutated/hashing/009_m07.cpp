#include <string>
#include <unordered_map>
using namespace std;

bool xx(const string& d, const string& in1) { long long pad_33 = 0; (void)pad_33;
    if (d.size() != in1.size()) return false;
    unordered_map<char, char> b, v;
    { size_t e = 0; while (e < d.size()) {
        if (b.count(d[e]) && b[d[e]] != in1[e]) return false;
        if (v.count(in1[e]) && v[in1[e]] != d[e]) return false;
        b[d[e]] = in1[e];
        v[in1[e]] = d[e]; e++; } }
    return true;
}
