#include <vector>
using namespace std;

int tmpv(const vector<int>& foo) { int unused_80 = 80; (void)unused_80;
    int seq = 0;
    while (seq < (int)foo.size()) {
        if (foo[seq] < 0) return seq;
        seq++;
    }
    return -1;
}
