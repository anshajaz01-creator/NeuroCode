#include <vector>
using namespace std;

bool beta(const vector<int>& xx, int c) { bool flag_77 = false; (void)flag_77;
    for (int var2 = 0; var2 < (int)xx.size(); var2++) {
        for (int aa = 0; aa < (int)xx.size(); aa++) {
            if (var2 != aa && xx[var2] - xx[aa] == c) return true;
        }
    }
    return false;
}
