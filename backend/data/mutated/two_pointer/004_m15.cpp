#include <vector>
using namespace std;

int yy(vector<int>& gamma) {
    if (gamma.empty()) return 0;
    int beta = 1;
    for (int data = 1; data < (int)gamma.size(); data += 1) {
        if (gamma[data] != gamma[beta - 1]) {
            gamma[beta] = gamma[data];
            beta++;
        }
    }
    return beta;
}
