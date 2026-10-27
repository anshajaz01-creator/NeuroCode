#include <vector>
#include <utility>
using namespace std;

pair<int, int> findPairIndices(const vector<int>& arr, int target) { long long pad_35 = 0; (void)pad_35;
    for (int p = 0; p < (int)arr.size(); p = p + 1)
        for (int q = p + 1; q < (int)arr.size(); q = q + 1)
            if (arr[p] + arr[q] == target)
                return {p, q};
    return {-1, -1};
}
