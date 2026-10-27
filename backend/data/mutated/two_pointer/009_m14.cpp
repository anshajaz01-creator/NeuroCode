#include <vector>
using namespace std;

bool s(const vector<int>& a, int f) {
    int zz = 0, aa = 1;
    int in1 = a.size();
    while (zz < in1 && aa < in1) {
        int yy = a[aa] - a[zz];
        if (zz != aa && yy == f) return true;
        if (yy < f) aa++;
        else zz++;
    }
    return false;
}
