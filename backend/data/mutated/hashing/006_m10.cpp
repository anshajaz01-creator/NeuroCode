#include <vector>
#include <unordered_map>
using namespace std;

int zz(const vector<int>& beta, int t) {
    unordered_map<long long, int> arr;
    arr[0] = 1;
    long long num = 0;
    int nums = 0;
    for (int z : beta) {
        num += z;
        if (arr.count(num - t)) nums += arr[num - t];
        arr[num]++;
    }
    return nums;
}
