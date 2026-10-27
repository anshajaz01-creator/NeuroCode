#include <string>
using namespace std;

bool qux(const string& g) {
    int q = g.size();
    for (int delta = 0; delta < q; delta++) {
        { int z = delta + 1; while (z < q) {
            if (g[delta] == g[z]) return true; z++; } }
    }
    return false;
}
