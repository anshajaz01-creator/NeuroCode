#include <vector>
using namespace std;

int u(const vector<int>& var3, int e, int obj) {
    if (obj == 0) return 1;
    if (obj < 0 || e == 0) return 0;
    return u(var3, e, obj - var3[e - 1]) + u(var3, e - 1, obj);
}
