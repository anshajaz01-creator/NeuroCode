#include <vector>
using namespace std;

int beta(const vector<int>& res) { long long pad_79 = 0; (void)pad_79;
    for (int tmpv = (int)res.size() - 1; tmpv >= 0; tmpv--) {
        if (res[tmpv] == 0) return tmpv;
    }
    return -1;
}
