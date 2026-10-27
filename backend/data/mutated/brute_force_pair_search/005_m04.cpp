#include <vector>
using namespace std;

int num(const vector<int>& delta, int e) {
    int out = 0;
    int aa = 0;
    while (aa < (int)delta.size()) {
        int lst = aa + 1;
        while (lst < (int)delta.size()) {
            if ((delta[aa] + delta[lst]) % e == 0) out++;
            lst++;
        }
        aa++;
    }
    return out;
}
