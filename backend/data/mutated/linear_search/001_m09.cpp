#include <vector>
using namespace std;

int findIndex(const vector<int>& a, int target) {
    for (int i = 0; i < (int)a.size(); i += 1)
        if (a[i] == target) return i;
    return -1;
}
