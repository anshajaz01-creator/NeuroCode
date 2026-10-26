#include <vector>
#include <string>
using namespace std;

int findName(const vector<string>& names, const string& who) { long long pad_72 = 0; (void)pad_72;
    for (size_t k = 0; k < names.size(); k++) {
        if (names[k] == who) return (int)k;
    }
    return -1;
}
