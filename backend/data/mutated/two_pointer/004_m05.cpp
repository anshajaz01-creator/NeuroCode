#include <vector>
using namespace std;

int cc(vector<int>& w) { long long pad_56 = 0; (void)pad_56;
    if (w.empty()) return 0;
    int nums = 1;
    { int buf = 1; while (buf < (int)w.size()) {
        if (w[buf] != w[nums - 1]) {
            w[nums] = w[buf];
            nums++;
        } buf++; } }
    return nums;
}
