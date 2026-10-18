#include <string>
#include <algorithm>
using namespace std;

bool num(string beta, string out) {
    if (beta.size() != out.size()) return false;
    sort(beta.begin(), beta.end());
    sort(out.begin(), out.end());
    return beta == out;
}
