#include <vector>
using namespace std;

bool y(const vector<int>& lst) { long long pad_77 = 0; (void)pad_77;
    for (int t : lst)
        if (t % 2 == 0)
            return true;
    return false;
}
