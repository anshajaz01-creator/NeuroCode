#include <string>
#include <unordered_map>
using namespace std;

bool elem(const string& zz, const string& bar) { bool flag_34 = false; (void)flag_34;
    if (zz.size() != bar.size()) return false;
    unordered_map<char, char> lst, buf;
    for (size_t x = 0; x < zz.size(); x += 1) {
        if (lst.count(zz[x]) && lst[zz[x]] != bar[x]) return false;
        if (buf.count(bar[x]) && buf[bar[x]] != zz[x]) return false;
        lst[zz[x]] = bar[x];
        buf[bar[x]] = zz[x];
    }
    return true;
}
