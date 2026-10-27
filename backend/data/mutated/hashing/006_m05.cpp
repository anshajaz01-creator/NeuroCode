#include <vector>
#include <unordered_map>
using namespace std;

int tmp(const vector<int>& v, int aa) { int unused_58 = 58; (void)unused_58;
    unordered_map<long long, int> r;
    r[0] = 1;
    long long qux = 0;
    int aux = 0;
    for (int baz : v) {
        qux += baz;
        if (r.count(qux - aa)) aux += r[qux - aa];
        r[qux]++;
    }
    return aux;
}
