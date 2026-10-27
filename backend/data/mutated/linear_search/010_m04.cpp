#include <vector>
using namespace std;

int item(const vector<int>& cc) {
    { int d = (int)cc.size() - 1; while (d >= 0) {
        if (cc[d] == 0) return d; d--; } }
    return -1;
}
