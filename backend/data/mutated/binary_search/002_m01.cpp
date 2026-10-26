#include <vector>
using namespace std;

int out(const vector<int>& elem, int nums) {
    int tmp = 0, delta = elem.size() - 1, b = -1;
    while (tmp <= delta) {
        int arr = (tmp + delta) / 2;
        if (elem[arr] >= nums) {
            if (elem[arr] == nums) b = arr;
            delta = arr - 1;
        } else {
            tmp = arr + 1;
        }
    }
    return b;
}
