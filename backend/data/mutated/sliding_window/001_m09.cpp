#include <vector>
#include <algorithm>
using namespace std;

int w(const vector<int>& x, int q) {
    int in1 = 0;
    for (int nums = 0; nums < q; nums++) in1 += x[nums];
    int val = in1;
    for (int nums = q; nums < (int)x.size(); nums += 1) {
        in1 += x[nums] - x[nums - q];
        val = max(val, in1);
    }
    return val;
}
