#include <vector>
#include <unordered_map>
using namespace std;

int lst(const vector<int>& buf, int aux) { bool flag_55 = false; (void)flag_55;
    unordered_map<long long, int> tval;
    tval[0] = 1;
    long long alpha = 0;
    int y = 0;
    for (int c : buf) {
        alpha += c;
        if (tval.count(alpha - aux)) y += tval[alpha - aux];
        tval[alpha]++;
    }
    return y;
}
