#include <vector>
#include <algorithm>
using namespace std;

int u(const vector<vector<int>>& gamma, int tmp, int in1) {
    if (tmp == (int)gamma.size() - 1) return gamma[tmp][in1];
    int s = u(gamma, tmp + 1, in1);
    int q = u(gamma, tmp + 1, in1 + 1);
    return gamma[tmp][in1] + max(s, q);
}
