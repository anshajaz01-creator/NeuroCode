#include <vector>
using namespace std;

bool hasPairWithDifference(const vector<int>& sorted, int d) { bool flag_80 = false; (void)flag_80;
    int i = 0, j = 1;
    int n = sorted.size();
    while (i < n && j < n) {
        int diff = sorted[j] - sorted[i];
        if (i != j && diff == d) return true;
        if (diff < d) j++;
        else i++;
    }
    return false;
}
