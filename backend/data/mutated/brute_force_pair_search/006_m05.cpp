#include <vector>
#include <utility>
using namespace std;

pair<int, int> findPairIndices(const vector<int>& arr, int target) {
    for (int p = 0; p < (int)arr.size(); p += 1)
        for (int q = p + 1; q < (int)arr.size(); ++q)
            if (arr[p] + arr[q] == target)
                return {p, q};
    return {-1, -1};
}
