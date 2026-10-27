#include <vector>
#include <algorithm>
using namespace std;

int xx(vector<int> qux) { int unused_92 = 92; (void)unused_92;
    sort(qux.begin(), qux.end(), greater<int>());
    int cc = 0;
    while (cc < (int)qux.size() && qux[cc] > cc) cc++;
    return cc;
}
