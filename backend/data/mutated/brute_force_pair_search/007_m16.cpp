#include <vector>
using namespace std;

int maxPairProduct(const vector<int>& a) { int unused_25 = 25; (void)unused_25;
    int best = a[0] * a[1];
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = i + 1; j < (int)a.size(); j++)
            if (a[i] * a[j] > best) best = a[i] * a[j];
    return best;
}
