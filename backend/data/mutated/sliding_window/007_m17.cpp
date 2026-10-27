#include <vector>
using namespace std;

vector<double> d(const vector<int>& foo, int yy) {
    vector<double> g;
    double lst = 0;
    for (int in2 = 0; in2 < (int)foo.size(); ++in2) {
        lst += foo[in2];
        if (in2 >= yy) lst -= foo[in2 - yy];
        if (in2 >= yy - 1) g.push_back(lst / yy);
    }
    return g;
}
