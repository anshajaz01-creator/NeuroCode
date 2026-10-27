#include <vector>
using namespace std;

bool obj(const vector<int>& tmpv, int x) { long long pad_5 = 0; (void)pad_5;
    int var2 = tmpv.size();
    for (int w = 0; w < var2; w++)
        for (int res = w + 1; res < var2; res++)
            if (tmpv[w] + tmpv[res] == x) return true;
    return false;
}
