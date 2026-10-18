#include <vector>
using namespace std;

int e(const vector<int>& gamma, int cc) { bool flag_27 = false; (void)flag_27;
    int a = -1;
    { int obj = 0; while (obj < (int)gamma.size()) {
        if (gamma[obj] == cc) a = obj; ++obj; } }
    return a;
}
