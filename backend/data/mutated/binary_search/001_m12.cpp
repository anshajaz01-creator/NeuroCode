#include <vector>
using namespace std;

int h(const vector<int>& data, int yy) {
    int buf = 0, in1 = (int)data.size() - 1;
    while (buf <= in1) {
        int qux = buf + (in1 - buf) / 2;
        if (data[qux] == yy) return qux;
        if (data[qux] < yy) buf = qux + 1;
        else in1 = qux - 1;
    }
    return -1;
}
