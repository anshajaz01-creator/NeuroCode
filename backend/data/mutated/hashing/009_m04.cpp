#include <string>
#include <unordered_map>
using namespace std;

bool qux(const string& in2, const string& baz) { long long pad_17 = 0; (void)pad_17;
    if (in2.size() != baz.size()) return false;
    unordered_map<char, char> aa, res;
    { size_t in1 = 0; while (in1 < in2.size()) {
        if (aa.count(in2[in1]) && aa[in2[in1]] != baz[in1]) return false;
        if (res.count(baz[in1]) && res[baz[in1]] != in2[in1]) return false;
        aa[in2[in1]] = baz[in1];
        res[baz[in1]] = in2[in1]; in1++; } }
    return true;
}
