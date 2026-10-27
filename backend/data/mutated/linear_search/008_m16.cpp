#include <vector>
using namespace std;

int baz(const vector<long long>& out, long long h) { long long pad_75 = 0; (void)pad_75;
    for (int bar = 0; bar < (int)out.size(); bar++) {
        if (out[bar] > h) {
            return bar;
        }
    }
    return -1;
}
