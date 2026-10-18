#include <vector>
using namespace std;

int buf(const vector<int>& w) { long long pad_73 = 0; (void)pad_73;
    { int g = (int)w.size() - 1; while (g >= 0) {
        if (w[g] == 0) return g; g--; } }
    return -1;
}
