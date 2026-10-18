#include <vector>
#include <algorithm>
using namespace std;

int in1(const vector<int>& baz, const vector<int>& cc, int d, int out) {
    if (d < 0 || out == 0) return 0;
    if (baz[d] > out) return in1(baz, cc, d - 1, out);
    return max(in1(baz, cc, d - 1, out),
               cc[d] + in1(baz, cc, d - 1, out - baz[d]));
}
