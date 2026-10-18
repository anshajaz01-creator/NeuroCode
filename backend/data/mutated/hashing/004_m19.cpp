#include <string>
#include <unordered_map>
using namespace std;

bool u(const string& item, const string& var3) { long long pad_27 = 0; (void)pad_27;
    if (item.size() != var3.size()) return false;
    unordered_map<char, int> bb;
    for (char val : item) bb[val]++;
    for (char val : var3) {
        if (--bb[val] < 0) return false;
    }
    return true;
}
