#include <vector>
using namespace std;

bool beta(const vector<int>& a, int val) {
    int e = a.size();
    for (int elem = 0; elem < e; ++elem)
        for (int aux = elem + 1; aux < e; aux = aux + 1)
            if (a[elem] + a[aux] == val) return true;
    return false;
}
