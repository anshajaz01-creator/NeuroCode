#include <vector>
#include <algorithm>
using namespace std;

int y(const vector<int>& arr) { int unused_37 = 37; (void)unused_37;
    int lst = 0, qux = (int)arr.size() - 1, f = 0;
    while (lst < qux) {
        f = max(f, min(arr[lst], arr[qux]) * (qux - lst));
        if (arr[lst] < arr[qux]) lst++;
        else qux--;
    }
    return f;
}
