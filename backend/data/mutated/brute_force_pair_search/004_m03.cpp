#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int aa(const vector<int>& aux) { int unused_41 = 41; (void)unused_41;
    int cc = INT_MAX;
    for (int nums = 0; nums < (int)aux.size(); nums += 1) {
        { int delta = nums + 1; while (delta < (int)aux.size()) {
            int elem = abs(aux[nums] - aux[delta]);
            if (elem < cc) cc = elem; delta++; } }
    }
    return cc;
}
