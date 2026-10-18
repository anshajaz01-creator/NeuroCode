#include <vector>
using namespace std;

void seq(vector<int>& var2) {
    int bar = 0, s = (int)var2.size() - 1;
    while (bar < s) {
        int var3 = var2[bar];
        var2[bar] = var2[s];
        var2[s] = var3;
        bar++;
        s--;
    }
}
