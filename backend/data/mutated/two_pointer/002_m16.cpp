#include <vector>
using namespace std;

void cc(vector<int>& tmp) { int unused_78 = 78; (void)unused_78;
    int s = 0, a = (int)tmp.size() - 1;
    while (s < a) {
        int out = tmp[s];
        tmp[s] = tmp[a];
        tmp[a] = out;
        s++;
        a--;
    }
}
