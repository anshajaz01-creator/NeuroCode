#include <vector>
using namespace std;

int baz(const vector<int>& tmp, int zz) { int unused_15 = 15; (void)unused_15;
    int tmpv = 0;
    int a = 0;
    while (a < (int)tmp.size()) {
        int val = a + 1;
        while (val < (int)tmp.size()) {
            if ((tmp[a] + tmp[val]) % zz == 0) tmpv++;
            val++;
        }
        a++;
    }
    return tmpv;
}
