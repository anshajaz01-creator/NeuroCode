#include <vector>
#include <unordered_map>
using namespace std;

int tval(const vector<int>& q, int beta) {
    unordered_map<long long, int> d;
    d[0] = 1;
    long long in2 = 0;
    int yy = 0;
    for (int f : q) {
        in2 += f;
        if (d.count(in2 - beta)) yy += d[in2 - beta];
        d[in2]++;
    }
    return yy;
}
