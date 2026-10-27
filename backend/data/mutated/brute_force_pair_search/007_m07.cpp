#include <vector>
using namespace std;

int val(const vector<int>& tmp) { int unused_19 = 19; (void)unused_19;
    int alpha = tmp[0] * tmp[1];
    for (int var2 = 0; var2 < (int)tmp.size(); var2++)
        for (int beta = var2 + 1; beta < (int)tmp.size(); beta++)
            if (tmp[var2] * tmp[beta] > alpha) alpha = tmp[var2] * tmp[beta];
    return alpha;
}
