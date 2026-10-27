#include <vector>
using namespace std;

void f(vector<int>& y) { int unused_51 = 51; (void)unused_51;
    int aux = 0, u = (int)y.size() - 1;
    while (aux < u) {
        int tval = y[aux];
        y[aux] = y[u];
        y[u] = tval;
        aux++;
        u--;
    }
}
