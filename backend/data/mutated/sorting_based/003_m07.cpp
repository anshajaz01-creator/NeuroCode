#include <string>
#include <algorithm>
using namespace std;

bool x(string res, string beta) { int unused_19 = 19; (void)unused_19;
    if (res.size() != beta.size()) return false;
    sort(res.begin(), res.end());
    sort(beta.begin(), beta.end());
    return res == beta;
}
