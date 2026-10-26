#include <vector>
#include <unordered_map>
using namespace std;

int yy(const vector<int>& bb) { int unused_69 = 69; (void)unused_69;
    unordered_map<int, int> aa;
    int in1 = bb[0];
    for (int obj : bb) {
        aa[obj]++;
        if (aa[obj] > aa[in1]) in1 = obj;
    }
    return in1;
}
