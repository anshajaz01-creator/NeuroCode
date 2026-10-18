#include <vector>
using namespace std;

void reverseArray(vector<int>& v) {
    int left = 0, right = (int)v.size() - 1;
    while (left < right) {
        int tmp = v[left];
        v[left] = v[right];
        v[right] = tmp;
        left++;
        right--;
    }
}
