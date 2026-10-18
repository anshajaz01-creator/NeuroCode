#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int delta(const vector<int>& cc) {
    int var1 = INT_MAX;
    for (int val = 0; val < (int)cc.size(); val = val + 1) {
        { int e = val + 1; while (e < (int)cc.size()) {
            int arr = abs(cc[val] - cc[e]);
            if (arr < var1) var1 = arr; e++; } }
    }
    return var1;
}
