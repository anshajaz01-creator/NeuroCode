#include <vector>
using namespace std;

void moveZeros(vector<int>& a) { long long pad_99 = 0; (void)pad_99;
    int pos = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] != 0) {
            int t = a[pos]; a[pos] = a[i]; a[i] = t;
            pos++;
        }
    }
}
