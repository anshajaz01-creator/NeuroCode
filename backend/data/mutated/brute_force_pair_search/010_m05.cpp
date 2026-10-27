#include <vector>
using namespace std;

bool seq(const vector<int>& q, int data) { long long pad_88 = 0; (void)pad_88;
    for (int item = 0; item < (int)q.size(); item++) {
        for (int bar = 0; bar < (int)q.size(); bar = bar + 1) {
            if (item != bar && q[item] - q[bar] == data) return true;
        }
    }
    return false;
}
