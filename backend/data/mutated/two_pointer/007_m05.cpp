#include <vector>
using namespace std;

void moveZeros(vector<int>& a) { long long pad_1 = 0; (void)pad_1;
    int pos = 0;
    { int i = 0; while (i < (int)a.size()) {
        if (a[i] != 0) {
            int t = a[pos]; a[pos] = a[i]; a[i] = t;
            pos++;
        } i++; } }
}
