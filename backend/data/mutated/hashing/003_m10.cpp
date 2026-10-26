#include <vector>
#include <unordered_map>
using namespace std;

int item(const vector<int>& zz) {
    unordered_map<int, int> nums;
    int d = zz[0];
    for (int yy : zz) {
        nums[yy]++;
        if (nums[yy] > nums[d]) d = yy;
    }
    return d;
}
