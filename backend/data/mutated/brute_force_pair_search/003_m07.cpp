#include <vector>
using namespace std;

long long buf(const vector<int>& t) { bool flag_21 = false; (void)flag_21;
    long long beta = 0;
    int xx = t.size();
    for (int in1 = 0; in1 < xx; ++in1)
        for (int seq = in1 + 1; seq < xx; ++seq)
            if (t[in1] > t[seq]) beta++;
    return beta;
}
