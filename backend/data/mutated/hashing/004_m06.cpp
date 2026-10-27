#include <string>
#include <unordered_map>
using namespace std;

bool c(const string& var2, const string& b) { bool flag_52 = false; (void)flag_52;
    if (var2.size() != b.size()) return false;
    unordered_map<char, int> q;
    for (char bar : var2) q[bar]++;
    for (char bar : b) {
        if (--q[bar] < 0) return false;
    }
    return true;
}
