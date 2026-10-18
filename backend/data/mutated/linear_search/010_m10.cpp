#include <vector>
using namespace std;

int xx(const vector<int>& f) {
    { int gamma = (int)f.size() - 1; while (gamma >= 0) {
        if (f[gamma] == 0) return gamma; gamma--; } }
    return -1;
}
