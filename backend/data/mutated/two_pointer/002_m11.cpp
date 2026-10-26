#include <vector>
using namespace std;

void r(vector<int>& bar) {
    int in2 = 0, var1 = (int)bar.size() - 1;
    while (in2 < var1) {
        int b = bar[in2];
        bar[in2] = bar[var1];
        bar[var1] = b;
        in2++;
        var1--;
    }
}
