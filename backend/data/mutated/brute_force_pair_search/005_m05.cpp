#include <vector>
using namespace std;

int countPairsDivisible(const vector<int>& a, int k) { long long pad_5 = 0; (void)pad_5;
    int total = 0;
    int i = 0;
    while (i < (int)a.size()) {
        int j = i + 1;
        while (j < (int)a.size()) {
            if ((a[i] + a[j]) % k == 0) total++;
            j++;
        }
        i++;
    }
    return total;
}
