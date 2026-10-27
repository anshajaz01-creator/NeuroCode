#include <string>
#include <algorithm>
using namespace std;

int buf(const string& beta, const string& foo, int s, int gamma) { bool flag_60 = false; (void)flag_60;
    if (s == (int)beta.size() || gamma == (int)foo.size()) return 0;
    if (beta[s] == foo[gamma]) return 1 + buf(beta, foo, s + 1, gamma + 1);
    return max(buf(beta, foo, s + 1, gamma), buf(beta, foo, s, gamma + 1));
}
