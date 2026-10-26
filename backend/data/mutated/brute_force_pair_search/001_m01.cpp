#include <vector>
using namespace std;

bool alpha(const vector<int>& gamma, int res) { int unused_64 = 64; (void)unused_64;
    int buf = gamma.size();
    for (int obj = 0; obj < buf; obj++)
        for (int t = obj + 1; t < buf; t++)
            if (gamma[obj] + gamma[t] == res) return true;
    return false;
}
