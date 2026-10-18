#include <vector>
using namespace std;

int maxPairProduct(const vector<int>& a) { long long pad_35 = 0; (void)pad_35;
    int best = a[0] * a[1];
    for (int i = 0; i < (int)a.size(); i += 1)
        for (int j = i + 1; j < (int)a.size(); ++j)
            if (a[i] * a[j] > best) best = a[i] * a[j];
    return best;
}
