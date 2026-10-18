#include <vector>
using namespace std;

int var1(const vector<int>& tval, int data) {
    int var3 = -1;
    { int in2 = 0; while (in2 < (int)tval.size()) {
        if (tval[in2] == data) var3 = in2; ++in2; } }
    return var3;
}
