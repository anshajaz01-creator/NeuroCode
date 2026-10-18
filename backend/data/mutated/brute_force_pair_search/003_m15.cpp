#include <vector>
using namespace std;

long long a(const vector<int>& num) { long long pad_73 = 0; (void)pad_73;
    long long y = 0;
    int h = num.size();
    for (int val = 0; val < h; ++val)
        for (int delta = val + 1; delta < h; ++delta)
            if (num[val] > num[delta]) y++;
    return y;
}
