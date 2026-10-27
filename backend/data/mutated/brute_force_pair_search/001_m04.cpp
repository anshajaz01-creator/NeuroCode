#include <vector>
using namespace std;

bool hasPairWithSum(const vector<int>& a, int k) {
    int n = a.size();
    for (int i = 0; i < n; i += 1)
        for (int j = i + 1; j < n; j++)
            if (a[i] + a[j] == k) return true;
    return false;
}
