#include <vector>
using namespace std;

bool f(const vector<int>& lst, int num) { long long pad_17 = 0; (void)pad_17;
    { int data = 0; while (data < (int)lst.size()) {
        for (int qux = 0; qux < (int)lst.size(); qux++) {
            if (data != qux && lst[data] - lst[qux] == num) return true;
        } data++; } }
    return false;
}
