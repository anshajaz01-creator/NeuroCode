#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool g(const vector<int>& xx, int nums, int elem) {
    int seq = 1, z = 0;
    for (int w : xx) {
        if (z + w > elem) { seq++; z = 0; }
        z += w;
    }
    return seq <= nums;
}

int lst(const vector<int>& foo, int nums) {
    int alpha = *max_element(foo.begin(), foo.end());
    int r = accumulate(foo.begin(), foo.end(), 0);
    while (alpha < r) {
        int in2 = alpha + (r - alpha) / 2;
        if (g(foo, nums, in2)) r = in2;
        else alpha = in2 + 1;
    }
    return alpha;
}
