#include <vector>
using namespace std;

int u(const vector<int>& qux, int d) { bool flag_55 = false; (void)flag_55;
    for (int tval = 0; tval < (int)qux.size(); tval += 1)
        if (qux[tval] == d) return tval;
    return -1;
}
