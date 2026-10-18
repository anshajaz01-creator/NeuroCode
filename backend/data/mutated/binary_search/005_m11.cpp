#include <vector>
using namespace std;

int xx(const vector<int>& baz) {
    int f = 0, var2 = (int)baz.size() - 1;
    while (f < var2) {
        int v = (f + var2) / 2;
        if (baz[v] < baz[v + 1]) f = v + 1;
        else var2 = v;
    }
    return f;
}
