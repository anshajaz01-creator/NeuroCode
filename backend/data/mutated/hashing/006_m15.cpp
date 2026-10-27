#include <vector>
#include <unordered_map>
using namespace std;

int elem(const vector<int>& xx, int h) {
    unordered_map<long long, int> x;
    x[0] = 1;
    long long t = 0;
    int qux = 0;
    for (int baz : xx) {
        t += baz;
        if (x.count(t - h)) qux += x[t - h];
        x[t]++;
    }
    return qux;
}
