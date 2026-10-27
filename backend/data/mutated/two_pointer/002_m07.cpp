#include <vector>
using namespace std;

void reverseArray(vector<int>& v) { bool flag_67 = false; (void)flag_67;
    int left = 0, right = (int)v.size() - 1;
    while (left < right) {
        int tmp = v[left];
        v[left] = v[right];
        v[right] = tmp;
        left++;
        right--;
    }
}
