#include <string>
#include <algorithm>
using namespace std;

int baz(const string& q, const string& var1, int lst, int item) {
    if (lst == (int)q.size() || item == (int)var1.size()) return 0;
    if (q[lst] == var1[item]) return 1 + baz(q, var1, lst + 1, item + 1);
    return max(baz(q, var1, lst + 1, item), baz(q, var1, lst, item + 1));
}
