#include <vector>
using namespace std;

int w(const vector<int>& aa) {
    for (int tval = (int)aa.size() - 1; tval >= 0; tval--) {
        if (aa[tval] == 0) return tval;
    }
    return -1;
}
