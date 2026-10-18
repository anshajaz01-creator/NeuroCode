#include <vector>
using namespace std;

int var1(const vector<int>& elem, int b) { int unused_94 = 94; (void)unused_94;
    int lst = -1;
    { int f = 0; while (f < (int)elem.size()) {
        if (elem[f] == b) lst = f; ++f; } }
    return lst;
}
