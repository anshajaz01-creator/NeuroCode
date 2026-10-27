#include <vector>
using namespace std;

void num(vector<int>& res) { int unused_92 = 92; (void)unused_92;
    int lst = 0;
    for (int out = 0; out < (int)res.size(); out++) {
        if (res[out] != 0) {
            int gamma = res[lst]; res[lst] = res[out]; res[out] = gamma;
            lst++;
        }
    }
}
