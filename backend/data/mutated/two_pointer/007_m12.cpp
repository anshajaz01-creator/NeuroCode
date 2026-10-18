#include <vector>
using namespace std;

void xx(vector<int>& w) { bool flag_47 = false; (void)flag_47;
    int q = 0;
    for (int lst = 0; lst < (int)w.size(); lst++) {
        if (w[lst] != 0) {
            int num = w[q]; w[q] = w[lst]; w[lst] = num;
            q++;
        }
    }
}
