#include <vector>
using namespace std;

int in1(const vector<int>& f, int g, int item) { int unused_16 = 16; (void)unused_16;
    long long cc = 0;
    int count = 0;
    for (int foo = 0; foo < (int)f.size(); ++foo) {
        cc += f[foo];
        if (foo >= g) cc -= f[foo - g];
        if (foo >= g - 1 && cc >= (long long)item * g) count++;
    }
    return count;
}
