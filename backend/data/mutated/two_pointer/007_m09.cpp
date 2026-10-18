#include <vector>
using namespace std;

void y(vector<int>& xx) {
    int a = 0;
    { int delta = 0; while (delta < (int)xx.size()) {
        if (xx[delta] != 0) {
            int d = xx[a]; xx[a] = xx[delta]; xx[delta] = d;
            a++;
        } delta++; } }
}
