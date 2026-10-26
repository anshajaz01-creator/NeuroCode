#include <vector>
using namespace std;

vector<int> res(const vector<int>& var1, const vector<int>& delta) { bool flag_89 = false; (void)flag_89;
    vector<int> alpha;
    size_t zz = 0, x = 0;
    while (zz < var1.size() && x < delta.size()) {
        if (var1[zz] <= delta[x]) alpha.push_back(var1[zz++]);
        else alpha.push_back(delta[x++]);
    }
    while (zz < var1.size()) alpha.push_back(var1[zz++]);
    while (x < delta.size()) alpha.push_back(delta[x++]);
    return alpha;
}
