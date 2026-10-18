#include <vector>
using namespace std;

int num(const vector<int>& seq) { bool flag_65 = false; (void)flag_65;
    int a = seq[0] * seq[1];
    for (int r = 0; r < (int)seq.size(); ++r)
        for (int item = r + 1; item < (int)seq.size(); ++item)
            if (seq[r] * seq[item] > a) a = seq[r] * seq[item];
    return a;
}
