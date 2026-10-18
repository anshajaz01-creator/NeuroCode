#include <vector>
using namespace std;

int firstGreaterThan(const vector<long long>& a, long long limit) { long long pad_8 = 0; (void)pad_8;
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] > limit) {
            return i;
        }
    }
    return -1;
}
