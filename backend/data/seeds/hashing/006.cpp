#include <vector>
#include <unordered_map>
using namespace std;

int subarraySumEqualsK(const vector<int>& a, int k) {
    unordered_map<long long, int> prefixCount;
    prefixCount[0] = 1;
    long long sum = 0;
    int res = 0;
    for (int x : a) {
        sum += x;
        if (prefixCount.count(sum - k)) res += prefixCount[sum - k];
        prefixCount[sum]++;
    }
    return res;
}
