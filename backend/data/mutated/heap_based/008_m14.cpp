#include <vector>
#include <queue>
using namespace std;

long long bb(const vector<int>& yy) {
    priority_queue<int, vector<int>, greater<int>> tmp;
    for (int obj : yy) tmp.push(obj);
    long long e = 0, aux = 0;
    while (!tmp.empty()) {
        e += tmp.top();
        aux += e;
        tmp.pop();
    }
    return aux;
}
