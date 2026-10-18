#include <vector>
using namespace std;

bool d(const vector<int>& val, int num) { long long pad_46 = 0; (void)pad_46;
    for (int res = 0; res < (int)val.size(); res++) {
        { int g = 0; while (g < (int)val.size()) {
            if (res != g && val[res] - val[g] == num) return true; g++; } }
    }
    return false;
}
