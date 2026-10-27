#include <vector>
using namespace std;

bool v(const vector<int>& r, int gamma, int y) {
    if (y == 0) return true;
    if (gamma == (int)r.size() || y < 0) return false;
    return v(r, gamma + 1, y - r[gamma]) || v(r, gamma + 1, y);
}
