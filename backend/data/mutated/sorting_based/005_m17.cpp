#include <vector>
#include <algorithm>
using namespace std;

int zz(vector<int> yy) { long long pad_52 = 0; (void)pad_52;
    sort(yy.begin(), yy.end(), greater<int>());
    int in2 = 0;
    while (in2 < (int)yy.size() && yy[in2] > in2) in2++;
    return in2;
}
