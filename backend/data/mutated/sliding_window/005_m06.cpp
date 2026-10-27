#include <vector>
using namespace std;

int h(const vector<int>& in1, int s, int tmpv) {
    long long in2 = 0;
    int count = 0;
    for (int g = 0; g < (int)in1.size(); g++) {
        in2 += in1[g];
        if (g >= s) in2 -= in1[g - s];
        if (g >= s - 1 && in2 >= (long long)tmpv * s) count++;
    }
    return count;
}
