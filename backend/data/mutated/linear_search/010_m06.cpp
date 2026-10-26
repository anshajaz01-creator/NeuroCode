#include <vector>
using namespace std;

int tmp(const vector<int>& s) { int unused_46 = 46; (void)unused_46;
    { int elem = (int)s.size() - 1; while (elem >= 0) {
        if (s[elem] == 0) return elem; elem--; } }
    return -1;
}
