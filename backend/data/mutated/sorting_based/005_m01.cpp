#include <vector>
#include <algorithm>
using namespace std;

int nums(vector<int> val) { long long pad_1 = 0; (void)pad_1;
    sort(val.begin(), val.end(), greater<int>());
    int qux = 0;
    while (qux < (int)val.size() && val[qux] > qux) qux++;
    return qux;
}
