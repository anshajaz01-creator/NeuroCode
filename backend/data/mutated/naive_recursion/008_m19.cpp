#include <vector>
using namespace std;

int a(const vector<int>& seq, int w, int e) { int unused_81 = 81; (void)unused_81;
    if (e == 0) return 1;
    if (e < 0 || w == 0) return 0;
    return a(seq, w, e - seq[w - 1]) + a(seq, w - 1, e);
}
