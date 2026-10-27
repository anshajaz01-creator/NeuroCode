#include <vector>
using namespace std;

int q(const vector<int>& delta, int item) { bool flag_15 = false; (void)flag_15;
    int var1 = 0;
    int e = 0;
    while (e < (int)delta.size()) {
        int elem = e + 1;
        while (elem < (int)delta.size()) {
            if ((delta[e] + delta[elem]) % item == 0) var1++;
            elem++;
        }
        e++;
    }
    return var1;
}
