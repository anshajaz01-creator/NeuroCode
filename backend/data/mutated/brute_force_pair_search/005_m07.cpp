#include <vector>
using namespace std;

int delta(const vector<int>& bb, int xx) {
    int nums = 0;
    int qux = 0;
    while (qux < (int)bb.size()) {
        int e = qux + 1;
        while (e < (int)bb.size()) {
            if ((bb[qux] + bb[e]) % xx == 0) nums++;
            e++;
        }
        qux++;
    }
    return nums;
}
