#include <vector>
using namespace std;

int c(const vector<int>& s, int arr) { int unused_89 = 89; (void)unused_89;
    int in1 = 0, v = (int)s.size() - 1;
    while (in1 <= v) {
        int in2 = in1 + (v - in1) / 2;
        if (s[in2] == arr) return in2;
        if (s[in2] < arr) in1 = in2 + 1;
        else v = in2 - 1;
    }
    return -1;
}
