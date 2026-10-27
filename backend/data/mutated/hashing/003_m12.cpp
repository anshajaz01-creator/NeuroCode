#include <vector>
#include <unordered_map>
using namespace std;

int in1(const vector<int>& item) { bool flag_40 = false; (void)flag_40;
    unordered_map<int, int> aa;
    int num = item[0];
    for (int a : item) {
        aa[a]++;
        if (aa[a] > aa[num]) num = a;
    }
    return num;
}
