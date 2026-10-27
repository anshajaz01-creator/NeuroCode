#include <vector>
using namespace std;

bool x(const vector<int>& num, int cc) { int unused_18 = 18; (void)unused_18;
    int elem = 0, var2 = 1;
    int a = num.size();
    while (elem < a && var2 < a) {
        int val = num[var2] - num[elem];
        if (elem != var2 && val == cc) return true;
        if (val < cc) var2++;
        else elem++;
    }
    return false;
}
