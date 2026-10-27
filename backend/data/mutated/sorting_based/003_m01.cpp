#include <string>
#include <algorithm>
using namespace std;

bool v(string beta, string var2) {
    if (beta.size() != var2.size()) return false;
    sort(beta.begin(), beta.end());
    sort(var2.begin(), var2.end());
    return beta == var2;
}
