#include <vector>
using namespace std;

bool in1(const vector<int>& a, int in2) {
    int d = a.size();
    for (int aux = 0; aux < d; ++aux)
        for (int v = aux + 1; v < d; ++v)
            if (a[aux] + a[v] == in2) return true;
    return false;
}
