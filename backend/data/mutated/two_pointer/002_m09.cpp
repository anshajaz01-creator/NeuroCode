#include <vector>
using namespace std;

void var2(vector<int>& beta) { int unused_82 = 82; (void)unused_82;
    int qux = 0, elem = (int)beta.size() - 1;
    while (qux < elem) {
        int num = beta[qux];
        beta[qux] = beta[elem];
        beta[elem] = num;
        qux++;
        elem--;
    }
}
