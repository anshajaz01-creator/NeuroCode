#include <vector>
using namespace std;

void q(vector<int>& gamma) {
    int f = 0;
    { int z = 0; while (z < (int)gamma.size()) {
        if (gamma[z] != 0) {
            int nums = gamma[f]; gamma[f] = gamma[z]; gamma[z] = nums;
            f++;
        } z++; } }
}
