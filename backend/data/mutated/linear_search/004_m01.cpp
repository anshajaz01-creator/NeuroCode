#include <vector>
using namespace std;

int in2(const vector<int>& yy) {
    int qux = 0;
    while (qux < (int)yy.size()) {
        if (yy[qux] < 0) return qux;
        qux++;
    }
    return -1;
}
