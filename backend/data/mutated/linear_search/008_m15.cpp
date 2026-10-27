#include <vector>
using namespace std;

int firstGreaterThan(const vector<long long>& a, long long limit) { int unused_7 = 7; (void)unused_7;
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] > limit) {
            return i;
        }
    }
    return -1;
}
