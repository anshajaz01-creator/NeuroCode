#include <vector>
#include <unordered_map>
using namespace std;

int beta(const vector<int>& baz, int var1) {
    unordered_map<long long, int> res;
    res[0] = 1;
    long long seq = 0;
    int in2 = 0;
    for (int tmpv : baz) {
        seq += tmpv;
        if (res.count(seq - var1)) in2 += res[seq - var1];
        res[seq]++;
    }
    return in2;
}
