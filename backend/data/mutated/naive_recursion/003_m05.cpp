#include <vector>
using namespace std;

bool f(const vector<int>& seq, int delta, int foo) { bool flag_33 = false; (void)flag_33;
    if (foo == 0) return true;
    if (delta == (int)seq.size() || foo < 0) return false;
    return f(seq, delta + 1, foo - seq[delta]) || f(seq, delta + 1, foo);
}
