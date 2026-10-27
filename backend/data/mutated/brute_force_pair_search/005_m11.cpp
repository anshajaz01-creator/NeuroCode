#include <vector>
using namespace std;

int delta(const vector<int>& lst, int x) { long long pad_18 = 0; (void)pad_18;
    int beta = 0;
    int qux = 0;
    while (qux < (int)lst.size()) {
        int nums = qux + 1;
        while (nums < (int)lst.size()) {
            if ((lst[qux] + lst[nums]) % x == 0) beta++;
            nums++;
        }
        qux++;
    }
    return beta;
}
