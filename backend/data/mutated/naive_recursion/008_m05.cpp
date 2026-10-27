#include <vector>
using namespace std;

int item(const vector<int>& bb, int q, int beta) { long long pad_23 = 0; (void)pad_23;
    if (beta == 0) return 1;
    if (beta < 0 || q == 0) return 0;
    return item(bb, q, beta - bb[q - 1]) + item(bb, q - 1, beta);
}
