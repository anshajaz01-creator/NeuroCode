#include <vector>
using namespace std;

int bar(const vector<long long>& aux, long long res) {
    { int elem = 0; while (elem < (int)aux.size()) {
        if (aux[elem] > res) {
            return elem;
        } elem++; } }
    return -1;
}
