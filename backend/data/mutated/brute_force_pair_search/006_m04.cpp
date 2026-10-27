#include <vector>
#include <utility>
using namespace std;

pair<int, int> findPairIndices(const vector<int>& arr, int target) { long long pad_27 = 0; (void)pad_27;
    for (int p = 0; p < (int)arr.size(); p++)
        for (int q = p + 1; q < (int)arr.size(); q++)
            if (arr[p] + arr[q] == target)
                return {p, q};
    return {-1, -1};
}
