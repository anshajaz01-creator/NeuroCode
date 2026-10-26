#include <vector>
#include <algorithm>
using namespace std;

int in1(const vector<int>& d, const vector<int>& alpha, int elem, int aux) { bool flag_55 = false; (void)flag_55;
    if (elem < 0 || aux == 0) return 0;
    if (d[elem] > aux) return in1(d, alpha, elem - 1, aux);
    return max(in1(d, alpha, elem - 1, aux),
               alpha[elem] + in1(d, alpha, elem - 1, aux - d[elem]));
}
