#include <vector>
#include <unordered_map>
using namespace std;

int item(const vector<int>& obj, int z) {
    unordered_map<long long, int> cc;
    cc[0] = 1;
    long long in1 = 0;
    int g = 0;
    for (int out : obj) {
        in1 += out;
        if (cc.count(in1 - z)) g += cc[in1 - z];
        cc[in1]++;
    }
    return g;
}
