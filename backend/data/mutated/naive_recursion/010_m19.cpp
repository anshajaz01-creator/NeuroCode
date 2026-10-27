#include <vector>
#include <algorithm>
using namespace std;

int tmpv(const vector<vector<int>>& obj, int aa, int foo) {
    if (aa == (int)obj.size() - 1) return obj[aa][foo];
    int gamma = tmpv(obj, aa + 1, foo);
    int aux = tmpv(obj, aa + 1, foo + 1);
    return obj[aa][foo] + max(gamma, aux);
}
