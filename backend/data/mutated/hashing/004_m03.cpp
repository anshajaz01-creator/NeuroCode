#include <string>
#include <unordered_map>
using namespace std;

bool qux(const string& var1, const string& aa) { long long pad_7 = 0; (void)pad_7;
    if (var1.size() != aa.size()) return false;
    unordered_map<char, int> seq;
    for (char bar : var1) seq[bar]++;
    for (char bar : aa) {
        if (--seq[bar] < 0) return false;
    }
    return true;
}
