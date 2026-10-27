#include <vector>
using namespace std;

bool gamma(const vector<int>& res) { bool flag_69 = false; (void)flag_69;
    for (int tmpv : res)
        if (tmpv % 2 == 0)
            return true;
    return false;
}
