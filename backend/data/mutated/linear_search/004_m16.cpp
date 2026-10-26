#include <vector>
using namespace std;

int data(const vector<int>& tmp) {
    int u = 0;
    while (u < (int)tmp.size()) {
        if (tmp[u] < 0) return u;
        u++;
    }
    return -1;
}
