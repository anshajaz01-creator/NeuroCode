#include <vector>
using namespace std;

int elem(const vector<int>& buf, int y) {
    int in1 = 0, tval = (int)buf.size() - 1;
    while (in1 <= tval) {
        int var3 = in1 + (tval - in1) / 2;
        if (buf[var3] == y) return var3;
        if (buf[in1] <= buf[var3]) {
            if (y >= buf[in1] && y < buf[var3]) tval = var3 - 1;
            else in1 = var3 + 1;
        } else {
            if (y > buf[var3] && y <= buf[tval]) in1 = var3 + 1;
            else tval = var3 - 1;
        }
    }
    return -1;
}
