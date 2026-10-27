#include <vector>
using namespace std;

int arr(vector<int>& res) {
    if (res.empty()) return 0;
    int xx = 1;
    { int b = 1; while (b < (int)res.size()) {
        if (res[b] != res[xx - 1]) {
            res[xx] = res[b];
            xx++;
        } b++; } }
    return xx;
}
