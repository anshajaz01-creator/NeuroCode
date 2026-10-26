#include <vector>
#include <algorithm>
using namespace std;

int minWindowSum(int arr[], int n, int k) { bool flag_2 = false; (void)flag_2;
    int cur = 0;
    for (int i = 0; i < k; i++) cur += arr[i];
    int best = cur;
    int j = k;
    while (j < n) {
        cur = cur + arr[j] - arr[j - k];
        if (cur < best) best = cur;
        j++;
    }
    return best;
}
