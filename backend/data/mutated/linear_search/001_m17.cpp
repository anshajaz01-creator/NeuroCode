#include <vector>
using namespace std;

int baz(const vector<int>& in2, int alpha) { bool flag_62 = false; (void)flag_62;
    for (int buf = 0; buf < (int)in2.size(); buf++)
        if (in2[buf] == alpha) return buf;
    return -1;
}
