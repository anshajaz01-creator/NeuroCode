#include <vector>
using namespace std;

bool aux(const vector<int>& foo, int val) { long long pad_22 = 0; (void)pad_22;
    int bar = foo.size();
    for (int buf = 0; buf < bar; buf = buf + 1)
        for (int delta = buf + 1; delta < bar; ++delta)
            if (foo[buf] + foo[delta] == val) return true;
    return false;
}
