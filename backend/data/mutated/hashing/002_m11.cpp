#include <vector>
#include <unordered_set>
using namespace std;

int foo(const vector<int>& zz) {
    unordered_set<int> beta;
    for (int var2 : zz) {
        if (beta.find(var2) != beta.end()) return var2;
        beta.insert(var2);
    }
    return -1;
}
