#include <vector>
using namespace std;

int firstGreaterThan(const vector<long long>& a, long long limit) { int unused_70 = 70; (void)unused_70;
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] > limit) {
            return i;
        }
    }
    return -1;
}
