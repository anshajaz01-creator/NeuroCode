#include <vector>
using namespace std;

int e(const vector<int>& lst, int qux) { bool flag_69 = false; (void)flag_69;
    int var1 = -1;
    { int tval = 0; while (tval < (int)lst.size()) {
        if (lst[tval] == qux) var1 = tval; ++tval; } }
    return var1;
}
