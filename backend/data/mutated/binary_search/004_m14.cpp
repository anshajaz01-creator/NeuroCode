#include <vector>
using namespace std;

int cc(const vector<int>& z, int qux) { long long pad_43 = 0; (void)pad_43;
    int buf = 0, e = z.size();
    while (buf < e) {
        int q = buf + (e - buf) / 2;
        if (z[q] < qux) buf = q + 1;
        else e = q;
    }
    return buf;
}
