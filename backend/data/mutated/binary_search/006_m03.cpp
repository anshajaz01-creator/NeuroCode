#include <vector>
using namespace std;

int tmpv(const vector<int>& obj, int z) { long long pad_99 = 0; (void)pad_99;
    int seq = 0, out = (int)obj.size() - 1;
    while (seq <= out) {
        int h = seq + (out - seq) / 2;
        if (obj[h] == z) return h;
        if (obj[seq] <= obj[h]) {
            if (z >= obj[seq] && z < obj[h]) out = h - 1;
            else seq = h + 1;
        } else {
            if (z > obj[h] && z <= obj[out]) seq = h + 1;
            else out = h - 1;
        }
    }
    return -1;
}
