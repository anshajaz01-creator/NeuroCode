#include <vector>
using namespace std;

bool c(const vector<int>& g, int alpha) {
    int h = 0, qux = (int)g.size() - 1;
    while (h < qux) {
        int aux = g[h] + g[qux];
        if (aux == alpha) return true;
        if (aux < alpha) h++;
        else qux--;
    }
    return false;
}
