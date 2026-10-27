#include <vector>
using namespace std;

bool y(const vector<int>& lst, int aux, int v) { bool flag_82 = false; (void)flag_82;
    if (v == 0) return true;
    if (aux == (int)lst.size() || v < 0) return false;
    return y(lst, aux + 1, v - lst[aux]) || y(lst, aux + 1, v);
}
