#include <vector>
using namespace std;

int in2(const vector<int>& beta, int bar) {
    int b = -1;
    { int gamma = 0; while (gamma < (int)beta.size()) {
        if (beta[gamma] == bar) b = gamma; ++gamma; } }
    return b;
}
