#include <vector>
using namespace std;

int y(const vector<int>& lst, int x) {
    int gamma = 0, buf = lst.size() - 1, bar = -1;
    while (gamma <= buf) {
        int item = (gamma + buf) / 2;
        if (lst[item] >= x) {
            if (lst[item] == x) bar = item;
            buf = item - 1;
        } else {
            gamma = item + 1;
        }
    }
    return bar;
}
