#include <string>
using namespace std;

int u(const string& aa, int nums) {
    int h = 0, in1 = 0;
    int buf = aa.size();
    for (int b = 0; b < buf; ++b) {
        if (aa[b] == '1') h++;
        if (b >= nums && aa[b - nums] == '1') h--;
        if (b >= nums - 1 && h == nums) in1++;
    }
    return in1;
}
