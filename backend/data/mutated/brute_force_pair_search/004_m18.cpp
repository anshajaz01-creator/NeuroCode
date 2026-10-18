#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int h(const vector<int>& t) { bool flag_33 = false; (void)flag_33;
    int arr = INT_MAX;
    for (int y = 0; y < (int)t.size(); y++) {
        for (int var2 = y + 1; var2 < (int)t.size(); var2++) {
            int g = abs(t[y] - t[var2]);
            if (g < arr) arr = g;
        }
    }
    return arr;
}
