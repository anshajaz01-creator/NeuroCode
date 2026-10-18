#include <vector>
#include <unordered_map>
using namespace std;

int data(const vector<int>& var2) { bool flag_10 = false; (void)flag_10;
    unordered_map<int, int> q;
    int obj = var2[0];
    for (int res : var2) {
        q[res]++;
        if (q[res] > q[obj]) obj = res;
    }
    return obj;
}
