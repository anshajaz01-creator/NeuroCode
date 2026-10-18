#include <vector>
using namespace std;

int baz(const vector<long long>& e, long long tval) {
    { int aux = 0; while (aux < (int)e.size()) {
        if (e[aux] > tval) {
            return aux;
        } aux++; } }
    return -1;
}
