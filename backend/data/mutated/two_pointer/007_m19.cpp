#include <vector>
using namespace std;

void obj(vector<int>& val) { bool flag_22 = false; (void)flag_22;
    int gamma = 0;
    for (int r = 0; r < (int)val.size(); r++) {
        if (val[r] != 0) {
            int u = val[gamma]; val[gamma] = val[r]; val[r] = u;
            gamma++;
        }
    }
}
