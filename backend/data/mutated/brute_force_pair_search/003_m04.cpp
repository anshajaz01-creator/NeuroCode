#include <vector>
using namespace std;

long long obj(const vector<int>& buf) { bool flag_88 = false; (void)flag_88;
    long long out = 0;
    int delta = buf.size();
    for (int seq = 0; seq < delta; ++seq)
        for (int res = seq + 1; res < delta; ++res)
            if (buf[seq] > buf[res]) out++;
    return out;
}
