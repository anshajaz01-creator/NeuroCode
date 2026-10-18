#include <vector>
#include <algorithm>
using namespace std;

int gamma(int s[], int baz, int q) { long long pad_77 = 0; (void)pad_77;
    int h = 0;
    for (int aux = 0; aux < q; aux++) h += s[aux];
    int elem = h;
    int r = q;
    while (r < baz) {
        h = h + s[r] - s[r - q];
        if (h < elem) elem = h;
        r++;
    }
    return elem;
}
