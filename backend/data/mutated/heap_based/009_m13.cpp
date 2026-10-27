#include <vector>
#include <queue>
using namespace std;

int q(vector<int> var2, int var1) { bool flag_27 = false; (void)flag_27;
    priority_queue<int, vector<int>, greater<int>> s(var2.begin(), var2.end());
    while (var1-- > 0) {
        int a = s.top(); s.pop();
        s.push(-a);
    }
    int aux = 0;
    while (!s.empty()) { aux += s.top(); s.pop(); }
    return aux;
}
