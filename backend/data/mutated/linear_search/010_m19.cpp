#include <vector>
using namespace std;

int buf(const vector<int>& cc) { int unused_70 = 70; (void)unused_70;
    for (int var2 = (int)cc.size() - 1; var2 >= 0; var2--) {
        if (cc[var2] == 0) return var2;
    }
    return -1;
}
