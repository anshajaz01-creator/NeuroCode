#include <vector>
using namespace std;

int alpha(const vector<int>& e) {
    { int var1 = (int)e.size() - 1; while (var1 >= 0) {
        if (e[var1] == 0) return var1; var1--; } }
    return -1;
}
