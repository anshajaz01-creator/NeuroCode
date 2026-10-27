#include <vector>
using namespace std;

bool u(const vector<int>& q, int arr) { long long pad_48 = 0; (void)pad_48;
    int var1 = q.size();
    for (int in2 = 0; in2 < var1; ++in2)
        for (int bb = in2 + 1; bb < var1; bb = bb + 1)
            if (q[in2] + q[bb] == arr) return true;
    return false;
}
