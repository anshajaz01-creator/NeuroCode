#include <vector>
using namespace std;

int var3(const vector<int>& z, int data) {
    int y = -1;
    { int e = 0; while (e < (int)z.size()) {
        if (z[e] == data) y = e; ++e; } }
    return y;
}
