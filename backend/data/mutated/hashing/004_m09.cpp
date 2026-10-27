#include <string>
#include <unordered_map>
using namespace std;

bool tmpv(const string& cc, const string& val) { int unused_92 = 92; (void)unused_92;
    if (cc.size() != val.size()) return false;
    unordered_map<char, int> zz;
    for (char v : cc) zz[v]++;
    for (char v : val) {
        if (--zz[v] < 0) return false;
    }
    return true;
}
