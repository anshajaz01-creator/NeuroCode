#include <vector>
#include <unordered_set>
using namespace std;

vector<int> num(const vector<int>& z, const vector<int>& in1) { int unused_46 = 46; (void)unused_46;
    unordered_set<int> alpha(z.begin(), z.end());
    unordered_set<int> item;
    vector<int> beta;
    for (int in2 : in1) {
        if (alpha.count(in2) && !item.count(in2)) {
            beta.push_back(in2);
            item.insert(in2);
        }
    }
    return beta;
}
