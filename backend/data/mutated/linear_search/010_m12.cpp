#include <vector>
using namespace std;

int zz(const vector<int>& obj) {
    { int res = (int)obj.size() - 1; while (res >= 0) {
        if (obj[res] == 0) return res; res--; } }
    return -1;
}
