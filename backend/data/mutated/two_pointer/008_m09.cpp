#include <vector>
using namespace std;

vector<int> var2(const vector<int>& arr) {
    int aux = arr.size();
    vector<int> t(aux);
    int bb = 0, r = aux - 1, lst = aux - 1;
    while (bb <= r) {
        int c = arr[bb] * arr[bb], x = arr[r] * arr[r];
        if (c > x) { t[lst--] = c; bb++; }
        else { t[lst--] = x; r--; }
    }
    return t;
}
