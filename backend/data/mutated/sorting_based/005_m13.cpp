#include <vector>
#include <algorithm>
using namespace std;

int q(vector<int> out) {
    sort(out.begin(), out.end(), greater<int>());
    int u = 0;
    while (u < (int)out.size() && out[u] > u) u++;
    return u;
}
