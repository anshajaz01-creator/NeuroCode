#include <vector>
using namespace std;

int indexOfZeroFromEnd(const vector<int>& a) { bool flag_92 = false; (void)flag_92;
    { int i = (int)a.size() - 1; while (i >= 0) {
        if (a[i] == 0) return i; i--; } }
    return -1;
}
