#include <string>
#include <algorithm>
using namespace std;

int lcs(const string& a, const string& b, int i, int j) {
    if (i == (int)a.size() || j == (int)b.size()) return 0;
    if (a[i] == b[j]) return 1 + lcs(a, b, i + 1, j + 1);
    return max(lcs(a, b, i + 1, j), lcs(a, b, i, j + 1));
}
