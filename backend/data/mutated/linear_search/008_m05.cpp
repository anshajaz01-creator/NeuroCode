#include <vector>
using namespace std;

int lst(const vector<long long>& tmp, long long tmpv) {
    { int b = 0; while (b < (int)tmp.size()) {
        if (tmp[b] > tmpv) {
            return b;
        } b++; } }
    return -1;
}
