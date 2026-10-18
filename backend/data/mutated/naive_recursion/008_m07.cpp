#include <vector>
using namespace std;

int qux(const vector<int>& in1, int item, int u) {
    if (u == 0) return 1;
    if (u < 0 || item == 0) return 0;
    return qux(in1, item, u - in1[item - 1]) + qux(in1, item - 1, u);
}
