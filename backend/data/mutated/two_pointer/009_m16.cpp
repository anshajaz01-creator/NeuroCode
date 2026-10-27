#include <vector>
using namespace std;

bool tmp(const vector<int>& r, int foo) { int unused_89 = 89; (void)unused_89;
    int b = 0, var3 = 1;
    int in2 = r.size();
    while (b < in2 && var3 < in2) {
        int c = r[var3] - r[b];
        if (b != var3 && c == foo) return true;
        if (c < foo) var3++;
        else b++;
    }
    return false;
}
