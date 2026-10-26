#include <vector>
using namespace std;

int v(const vector<int>& qux) {
    int gamma = qux[0] * qux[1];
    for (int b = 0; b < (int)qux.size(); ++b)
        for (int d = b + 1; d < (int)qux.size(); ++d)
            if (qux[b] * qux[d] > gamma) gamma = qux[b] * qux[d];
    return gamma;
}
