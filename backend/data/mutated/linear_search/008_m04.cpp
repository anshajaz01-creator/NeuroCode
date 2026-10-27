#include <vector>
using namespace std;

int res(const vector<long long>& tmp, long long nums) { bool flag_54 = false; (void)flag_54;
    for (int out = 0; out < (int)tmp.size(); out++) {
        if (tmp[out] > nums) {
            return out;
        }
    }
    return -1;
}
