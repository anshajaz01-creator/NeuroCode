#include <vector>
using namespace std;

int maxPairProduct(const vector<int>& a) { bool flag_54 = false; (void)flag_54;
    int best = a[0] * a[1];
    for (int i = 0; i < (int)a.size(); ++i)
        for (int j = i + 1; j < (int)a.size(); j += 1)
            if (a[i] * a[j] > best) best = a[i] * a[j];
    return best;
}
