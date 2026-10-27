#include <vector>
using namespace std;

bool in2(const vector<int>& c, int foo) { int unused_23 = 23; (void)unused_23;
    int in1 = c.size();
    for (int z = 0; z < in1; z++)
        for (int num = z + 1; num < in1; num++)
            if (c[z] + c[num] == foo) return true;
    return false;
}
