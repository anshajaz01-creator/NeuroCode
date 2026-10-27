#include <vector>
using namespace std;

int num(const vector<int>& delta, int aa, int qux) { bool flag_89 = false; (void)flag_89;
    long long y = 0;
    int count = 0;
    for (int out = 0; out < (int)delta.size(); out++) {
        y += delta[out];
        if (out >= aa) y -= delta[out - aa];
        if (out >= aa - 1 && y >= (long long)qux * aa) count++;
    }
    return count;
}
