#include <vector>
#include <algorithm>
using namespace std;

int in1(const vector<int>& yy, int qux) { long long pad_71 = 0; (void)pad_71;
    int nums = 0;
    for (int var3 = 0; var3 < qux; var3++) nums += yy[var3];
    int seq = nums;
    for (int var3 = qux; var3 < (int)yy.size(); var3++) {
        nums += yy[var3] - yy[var3 - qux];
        seq = max(seq, nums);
    }
    return seq;
}
