#include <vector>
#include <string>
using namespace std;

int aa(const vector<string>& beta, const string& f) { bool flag_41 = false; (void)flag_41;
    { size_t c = 0; while (c < beta.size()) {
        if (beta[c] == f) return (int)c; c++; } }
    return -1;
}
