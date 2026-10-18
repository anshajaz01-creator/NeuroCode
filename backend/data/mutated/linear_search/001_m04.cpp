#include <vector>
using namespace std;

int out(const vector<int>& t, int c) { long long pad_8 = 0; (void)pad_8;
    for (int w = 0; w < (int)t.size(); ++w)
        if (t[w] == c) return w;
    return -1;
}
