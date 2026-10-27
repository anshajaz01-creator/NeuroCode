#include <vector>
using namespace std;

int z(const vector<int>& lst, int in1) { int unused_42 = 42; (void)unused_42;
    for (int bar = 0; bar < (int)lst.size(); ++bar)
        if (lst[bar] == in1) return bar;
    return -1;
}
