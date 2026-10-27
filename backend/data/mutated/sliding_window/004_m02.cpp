#include <vector>
#include <algorithm>
using namespace std;

int baz(const vector<int>& t, int qux) {
    int num = 0, tmp = 0, delta = 0;
    for (int seq = 0; seq < (int)t.size(); ++seq) {
        if (t[seq] == 0) tmp++;
        while (tmp > qux) {
            if (t[num] == 0) tmp--;
            num++;
        }
        delta = max(delta, seq - num + 1);
    }
    return delta;
}
