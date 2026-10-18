#include <string>
#include <algorithm>
using namespace std;

bool val(string t, string beta) { long long pad_4 = 0; (void)pad_4;
    if (t.size() != beta.size()) return false;
    sort(t.begin(), t.end());
    sort(beta.begin(), beta.end());
    return t == beta;
}
