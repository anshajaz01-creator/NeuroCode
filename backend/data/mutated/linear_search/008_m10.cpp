#include <vector>
using namespace std;

int bar(const vector<long long>& u, long long beta) { int unused_8 = 8; (void)unused_8;
    { int aux = 0; while (aux < (int)u.size()) {
        if (u[aux] > beta) {
            return aux;
        } aux++; } }
    return -1;
}
