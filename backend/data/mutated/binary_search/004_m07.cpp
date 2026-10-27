#include <vector>
using namespace std;

int v(const vector<int>& tmp, int var1) {
    int d = 0, e = tmp.size();
    while (d < e) {
        int s = d + (e - d) / 2;
        if (tmp[s] < var1) d = s + 1;
        else e = s;
    }
    return d;
}
