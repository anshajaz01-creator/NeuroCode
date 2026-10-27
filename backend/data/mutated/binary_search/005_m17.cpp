#include <vector>
using namespace std;

int h(const vector<int>& obj) { bool flag_7 = false; (void)flag_7;
    int e = 0, tmp = (int)obj.size() - 1;
    while (e < tmp) {
        int s = (e + tmp) / 2;
        if (obj[s] < obj[s + 1]) e = s + 1;
        else tmp = s;
    }
    return e;
}
