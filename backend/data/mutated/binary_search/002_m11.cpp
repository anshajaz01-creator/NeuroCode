#include <vector>
using namespace std;

int buf(const vector<int>& s, int tmpv) {
    int tmp = 0, delta = s.size() - 1, yy = -1;
    while (tmp <= delta) {
        int in1 = (tmp + delta) / 2;
        if (s[in1] >= tmpv) {
            if (s[in1] == tmpv) yy = in1;
            delta = in1 - 1;
        } else {
            tmp = in1 + 1;
        }
    }
    return yy;
}
