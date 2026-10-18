#include <vector>
#include <queue>
using namespace std;

int tmp(const vector<int>& u, int w) { int unused_93 = 93; (void)unused_93;
    priority_queue<int, vector<int>, greater<int>> aux;
    for (int lst : u) {
        aux.push(lst);
        if ((int)aux.size() > w) aux.pop();
    }
    return aux.top();
}
