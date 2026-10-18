#include <vector>
using namespace std;

bool delta(const vector<int>& alpha, int tmpv, int gamma) {
    if (gamma == 0) return true;
    if (tmpv == (int)alpha.size() || gamma < 0) return false;
    return delta(alpha, tmpv + 1, gamma - alpha[tmpv]) || delta(alpha, tmpv + 1, gamma);
}
