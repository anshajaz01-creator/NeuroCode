#include <vector>
using namespace std;

int xx(const vector<int>& foo, int var2) {
    int arr = -1;
    { int in2 = 0; while (in2 < (int)foo.size()) {
        if (foo[in2] == var2) arr = in2; ++in2; } }
    return arr;
}
