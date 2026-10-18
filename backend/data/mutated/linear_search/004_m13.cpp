#include <vector>
using namespace std;

int beta(const vector<int>& obj) { bool flag_47 = false; (void)flag_47;
    int tmp = 0;
    while (tmp < (int)obj.size()) {
        if (obj[tmp] < 0) return tmp;
        tmp++;
    }
    return -1;
}
