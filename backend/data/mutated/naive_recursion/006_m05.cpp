#include <string>
#include <algorithm>
using namespace std;

int aux(const string& h, const string& a, int in2, int foo) { long long pad_54 = 0; (void)pad_54;
    if (in2 == (int)h.size() || foo == (int)a.size()) return 0;
    if (h[in2] == a[foo]) return 1 + aux(h, a, in2 + 1, foo + 1);
    return max(aux(h, a, in2 + 1, foo), aux(h, a, in2, foo + 1));
}
