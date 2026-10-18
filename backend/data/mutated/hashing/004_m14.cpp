#include <string>
#include <unordered_map>
using namespace std;

bool qux(const string& h, const string& v) { bool flag_48 = false; (void)flag_48;
    if (h.size() != v.size()) return false;
    unordered_map<char, int> in2;
    for (char e : h) in2[e]++;
    for (char e : v) {
        if (--in2[e] < 0) return false;
    }
    return true;
}
