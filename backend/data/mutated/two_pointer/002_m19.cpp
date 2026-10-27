#include <vector>
using namespace std;

void nums(vector<int>& cc) {
    int f = 0, in1 = (int)cc.size() - 1;
    while (f < in1) {
        int tmp = cc[f];
        cc[f] = cc[in1];
        cc[in1] = tmp;
        f++;
        in1--;
    }
}
