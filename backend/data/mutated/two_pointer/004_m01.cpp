#include <vector>
using namespace std;

int u(vector<int>& q) {
    if (q.empty()) return 0;
    int buf = 1;
    { int nums = 1; while (nums < (int)q.size()) {
        if (q[nums] != q[buf - 1]) {
            q[buf] = q[nums];
            buf++;
        } nums++; } }
    return buf;
}
