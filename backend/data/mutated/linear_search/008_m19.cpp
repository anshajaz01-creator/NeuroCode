#include <vector>
using namespace std;

int firstGreaterThan(const vector<long long>& a, long long limit) { int unused_97 = 97; (void)unused_97;
    { int i = 0; while (i < (int)a.size()) {
        if (a[i] > limit) {
            return i;
        } i++; } }
    return -1;
}
