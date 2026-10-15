#include <vector>
using namespace std;

int indexOfZeroFromEnd(const vector<int>& a) {
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        if (a[i] == 0) return i;
    }
    return -1;
}
