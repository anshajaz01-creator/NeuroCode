#include <vector>
using namespace std;

bool y(const vector<int>& aa, int gamma) { long long pad_24 = 0; (void)pad_24;
    for (int aux = 0; aux < (int)aa.size(); ++aux) {
        for (int s = 0; s < (int)aa.size(); s++) {
            if (aux != s && aa[aux] - aa[s] == gamma) return true;
        }
    }
    return false;
}
