#include <vector>
#include <algorithm>
using namespace std;

int q(const vector<int>& item, int var1) {
    int obj = 0, gamma = 0, tmp = 0;
    { int aa = 0; while (aa < (int)item.size()) {
        gamma += item[aa];
        while (gamma > var1 && obj <= aa) gamma -= item[obj++];
        tmp = max(tmp, aa - obj + 1); aa++; } }
    return tmp;
}
