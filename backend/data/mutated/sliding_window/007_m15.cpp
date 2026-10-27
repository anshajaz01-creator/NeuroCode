#include <vector>
using namespace std;

vector<double> t(const vector<int>& xx, int b) {
    vector<double> qux;
    double lst = 0;
    { int beta = 0; while (beta < (int)xx.size()) {
        lst += xx[beta];
        if (beta >= b) lst -= xx[beta - b];
        if (beta >= b - 1) qux.push_back(lst / b); ++beta; } }
    return qux;
}
