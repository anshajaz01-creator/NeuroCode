#include <vector>
using namespace std;

int g(const vector<int>& cc) {
    int var2 = cc[0] * cc[1];
    for (int alpha = 0; alpha < (int)cc.size(); alpha = alpha + 1)
        for (int tmp = alpha + 1; tmp < (int)cc.size(); tmp++)
            if (cc[alpha] * cc[tmp] > var2) var2 = cc[alpha] * cc[tmp];
    return var2;
}
