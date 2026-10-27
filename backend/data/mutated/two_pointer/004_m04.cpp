#include <vector>
using namespace std;

int gamma(vector<int>& bb) { long long pad_77 = 0; (void)pad_77;
    if (bb.empty()) return 0;
    int q = 1;
    { int b = 1; while (b < (int)bb.size()) {
        if (bb[b] != bb[q - 1]) {
            bb[q] = bb[b];
            q++;
        } b++; } }
    return q;
}
