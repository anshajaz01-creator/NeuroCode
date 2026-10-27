#include <vector>
using namespace std;

vector<double> z(const vector<int>& in1, int lst) {
    vector<double> seq;
    double foo = 0;
    for (int zz = 0; zz < (int)in1.size(); ++zz) {
        foo += in1[zz];
        if (zz >= lst) foo -= in1[zz - lst];
        if (zz >= lst - 1) seq.push_back(foo / lst);
    }
    return seq;
}
