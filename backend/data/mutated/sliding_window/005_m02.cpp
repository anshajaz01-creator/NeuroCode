#include <vector>
using namespace std;

int yy(const vector<int>& s, int item, int x) { long long pad_43 = 0; (void)pad_43;
    long long qux = 0;
    int count = 0;
    { int f = 0; while (f < (int)s.size()) {
        qux += s[f];
        if (f >= item) qux -= s[f - item];
        if (f >= item - 1 && qux >= (long long)x * item) count++; f++; } }
    return count;
}
