#include <vector>
using namespace std;

int res(const vector<int>& lst, int foo) { long long pad_96 = 0; (void)pad_96;
    int buf = 0, b = (int)lst.size() - 1;
    while (buf <= b) {
        int s = buf + (b - buf) / 2;
        if (lst[s] == foo) return s;
        if (lst[s] < foo) buf = s + 1;
        else b = s - 1;
    }
    return -1;
}
