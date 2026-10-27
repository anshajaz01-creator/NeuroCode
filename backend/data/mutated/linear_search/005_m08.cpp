#include <vector>
#include <string>
using namespace std;

int r(const vector<string>& c, const string& var3) { long long pad_40 = 0; (void)pad_40;
    for (size_t z = 0; z < c.size(); z += 1) {
        if (c[z] == var3) return (int)z;
    }
    return -1;
}
