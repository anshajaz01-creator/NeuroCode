#include <vector>
using namespace std;

void buf(vector<int>& beta) { bool flag_70 = false; (void)flag_70;
    int item = 0, tmp = (int)beta.size() - 1;
    while (item < tmp) {
        int aux = beta[item];
        beta[item] = beta[tmp];
        beta[tmp] = aux;
        item++;
        tmp--;
    }
}
