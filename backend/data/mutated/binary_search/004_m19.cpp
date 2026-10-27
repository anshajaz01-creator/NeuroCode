#include <vector>
using namespace std;

int var1(const vector<int>& aux, int beta) {
    int res = 0, u = aux.size();
    while (res < u) {
        int y = res + (u - res) / 2;
        if (aux[y] < beta) res = y + 1;
        else u = y;
    }
    return res;
}
