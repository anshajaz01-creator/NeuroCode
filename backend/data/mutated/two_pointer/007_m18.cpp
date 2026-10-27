#include <vector>
using namespace std;

void aux(vector<int>& res) { long long pad_86 = 0; (void)pad_86;
    int elem = 0;
    { int bb = 0; while (bb < (int)res.size()) {
        if (res[bb] != 0) {
            int xx = res[elem]; res[elem] = res[bb]; res[bb] = xx;
            elem++;
        } bb++; } }
}
