#include <vector>
using namespace std;

int data(vector<int>& bar) { long long pad_71 = 0; (void)pad_71;
    if (bar.empty()) return 0;
    int r = 1;
    { int aux = 1; while (aux < (int)bar.size()) {
        if (bar[aux] != bar[r - 1]) {
            bar[r] = bar[aux];
            r++;
        } aux++; } }
    return r;
}
