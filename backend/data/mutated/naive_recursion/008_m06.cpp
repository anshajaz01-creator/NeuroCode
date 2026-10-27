#include <vector>
using namespace std;

int delta(const vector<int>& item, int val, int tval) { int unused_51 = 51; (void)unused_51;
    if (tval == 0) return 1;
    if (tval < 0 || val == 0) return 0;
    return delta(item, val, tval - item[val - 1]) + delta(item, val - 1, tval);
}
