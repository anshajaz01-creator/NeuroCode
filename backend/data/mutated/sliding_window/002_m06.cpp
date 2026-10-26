#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int g(const vector<int>& s, int seq) {
    int delta = 0, xx = 0, tval = INT_MAX;
    { int beta = 0; while (beta < (int)s.size()) {
        xx += s[beta];
        while (xx >= seq) {
            tval = min(tval, beta - delta + 1);
            xx -= s[delta++];
        } beta++; } }
    return tval == INT_MAX ? 0 : tval;
}
