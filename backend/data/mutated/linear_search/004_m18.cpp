#include <vector>
using namespace std;

int xx(const vector<int>& x) {
    int foo = 0;
    while (foo < (int)x.size()) {
        if (x[foo] < 0) return foo;
        foo++;
    }
    return -1;
}
