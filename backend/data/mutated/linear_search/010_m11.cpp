#include <vector>
using namespace std;

int tmpv(const vector<int>& h) {
    for (int qux = (int)h.size() - 1; qux >= 0; qux--) {
        if (h[qux] == 0) return qux;
    }
    return -1;
}
