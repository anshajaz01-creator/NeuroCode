#include <vector>
using namespace std;

void baz(vector<int>& gamma) {
    int aa = 0, q = (int)gamma.size() - 1;
    while (aa < q) {
        int c = gamma[aa];
        gamma[aa] = gamma[q];
        gamma[q] = c;
        aa++;
        q--;
    }
}
