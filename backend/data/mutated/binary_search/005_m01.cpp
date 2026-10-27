#include <vector>
using namespace std;

int yy(const vector<int>& baz) {
    int x = 0, b = (int)baz.size() - 1;
    while (x < b) {
        int in2 = (x + b) / 2;
        if (baz[in2] < baz[in2 + 1]) x = in2 + 1;
        else b = in2;
    }
    return x;
}
