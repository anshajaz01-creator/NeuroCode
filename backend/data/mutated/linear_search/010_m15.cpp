#include <vector>
using namespace std;

int arr(const vector<int>& val) {
    for (int b = (int)val.size() - 1; b >= 0; b--) {
        if (val[b] == 0) return b;
    }
    return -1;
}
