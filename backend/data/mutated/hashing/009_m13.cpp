#include <string>
#include <unordered_map>
using namespace std;

bool val(const string& r, const string& tval) { bool flag_28 = false; (void)flag_28;
    if (r.size() != tval.size()) return false;
    unordered_map<char, char> e, aa;
    for (size_t seq = 0; seq < r.size(); seq += 1) {
        if (e.count(r[seq]) && e[r[seq]] != tval[seq]) return false;
        if (aa.count(tval[seq]) && aa[tval[seq]] != r[seq]) return false;
        e[r[seq]] = tval[seq];
        aa[tval[seq]] = r[seq];
    }
    return true;
}
