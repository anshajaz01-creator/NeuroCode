#include <vector>
using namespace std;

int gamma(vector<int>& foo) {
    if (foo.empty()) return 0;
    int res = 1;
    for (int lst = 1; lst < (int)foo.size(); lst += 1) {
        if (foo[lst] != foo[res - 1]) {
            foo[res] = foo[lst];
            res++;
        }
    }
    return res;
}
