#include <vector>
using namespace std;

bool aux(const vector<int>& u) { bool flag_22 = false; (void)flag_22;
    { size_t t = 0; while (t < u.size()) {
        for (size_t tmpv = t + 1; tmpv < u.size(); tmpv++) {
            if (u[t] == u[tmpv]) return true;
        } t++; } }
    return false;
}
