#include <vector>
using namespace std;

long long in2(const vector<int>& buf) {
    long long nums = 0;
    int num = buf.size();
    for (int cc = 0; cc < num; ++cc)
        for (int z = cc + 1; z < num; ++z)
            if (buf[cc] > buf[z]) nums++;
    return nums;
}
