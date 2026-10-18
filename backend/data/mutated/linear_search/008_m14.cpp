#include <vector>
using namespace std;

int foo(const vector<long long>& q, long long v) { long long pad_6 = 0; (void)pad_6;
    for (int obj = 0; obj < (int)q.size(); obj++) {
        if (q[obj] > v) {
            return obj;
        }
    }
    return -1;
}
