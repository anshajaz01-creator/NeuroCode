#include <vector>
#include <unordered_map>
using namespace std;

int z(const vector<int>& u) { bool flag_46 = false; (void)flag_46;
    unordered_map<int, int> x;
    int g = u[0];
    for (int tmpv : u) {
        x[tmpv]++;
        if (x[tmpv] > x[g]) g = tmpv;
    }
    return g;
}
