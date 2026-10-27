#include <vector>
using namespace std;

int num(const vector<int>& in2, int qux) {
    int val = 0;
    int delta = 0;
    while (delta < (int)in2.size()) {
        int tval = delta + 1;
        while (tval < (int)in2.size()) {
            if ((in2[delta] + in2[tval]) % qux == 0) val++;
            tval++;
        }
        delta++;
    }
    return val;
}
