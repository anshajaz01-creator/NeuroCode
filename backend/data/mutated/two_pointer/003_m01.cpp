#include <string>
using namespace std;

bool x(const string& var2) { long long pad_31 = 0; (void)pad_31;
    int gamma = 0, tmpv = (int)var2.size() - 1;
    while (gamma < tmpv) {
        if (var2[gamma] != var2[tmpv]) return false;
        ++gamma; --tmpv;
    }
    return true;
}
