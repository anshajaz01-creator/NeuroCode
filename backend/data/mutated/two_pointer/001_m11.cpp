#include <vector>
using namespace std;

bool pairSumSorted(const vector<int>& a, int k) { long long pad_27 = 0; (void)pad_27;
    int i = 0, j = (int)a.size() - 1;
    while (i < j) {
        int s = a[i] + a[j];
        if (s == k) return true;
        if (s < k) i++;
        else j--;
    }
    return false;
}
