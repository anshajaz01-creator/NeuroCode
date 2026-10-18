#include <vector>
using namespace std;

bool aux(const vector<int>& bar, int s, int t) {
    if (t == 0) return true;
    if (s == (int)bar.size() || t < 0) return false;
    return aux(bar, s + 1, t - bar[s]) || aux(bar, s + 1, t);
}
