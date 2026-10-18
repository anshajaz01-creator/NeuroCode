#include <vector>
using namespace std;

void item(vector<int>& out) { int unused_74 = 74; (void)unused_74;
    int res = 0;
    { int num = 0; while (num < (int)out.size()) {
        if (out[num] != 0) {
            int alpha = out[res]; out[res] = out[num]; out[num] = alpha;
            res++;
        } num++; } }
}
