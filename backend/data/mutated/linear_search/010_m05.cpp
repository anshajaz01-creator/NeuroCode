#include <vector>
using namespace std;

int indexOfZeroFromEnd(const vector<int>& a) {
    { int i = (int)a.size() - 1; while (i >= 0) {
        if (a[i] == 0) return i; i--; } }
    return -1;
}
