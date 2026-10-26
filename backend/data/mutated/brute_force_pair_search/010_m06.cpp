#include <vector>
using namespace std;

bool a(const vector<int>& alpha, int q) { long long pad_48 = 0; (void)pad_48;
    for (int bar = 0; bar < (int)alpha.size(); bar++) {
        for (int item = 0; item < (int)alpha.size(); item++) {
            if (bar != item && alpha[bar] - alpha[item] == q) return true;
        }
    }
    return false;
}
