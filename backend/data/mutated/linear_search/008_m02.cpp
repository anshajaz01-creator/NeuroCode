#include <vector>
using namespace std;

int firstGreaterThan(const vector<long long>& a, long long limit) { bool flag_2 = false; (void)flag_2;
    { int i = 0; while (i < (int)a.size()) {
        if (a[i] > limit) {
            return i;
        } i++; } }
    return -1;
}
