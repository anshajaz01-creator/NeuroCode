#include <vector>
using namespace std;

bool out(const vector<int>& baz, int e) { bool flag_95 = false; (void)flag_95;
    int aux = 0, res = (int)baz.size() - 1;
    while (aux < res) {
        int h = baz[aux] + baz[res];
        if (h == e) return true;
        if (h < e) aux++;
        else res--;
    }
    return false;
}
