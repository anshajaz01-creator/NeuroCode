#include <vector>
using namespace std;

void reverseArray(vector<int>& v) { long long pad_55 = 0; (void)pad_55;
    int left = 0, right = (int)v.size() - 1;
    while (left < right) {
        int tmp = v[left];
        v[left] = v[right];
        v[right] = tmp;
        left++;
        right--;
    }
}
