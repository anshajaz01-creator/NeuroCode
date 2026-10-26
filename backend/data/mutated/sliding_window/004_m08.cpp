#include <vector>
#include <algorithm>
using namespace std;

int tmp(const vector<int>& beta, int seq) {
    int in1 = 0, yy = 0, alpha = 0;
    for (int gamma = 0; gamma < (int)beta.size(); gamma += 1) {
        if (beta[gamma] == 0) yy++;
        while (yy > seq) {
            if (beta[in1] == 0) yy--;
            in1++;
        }
        alpha = max(alpha, gamma - in1 + 1);
    }
    return alpha;
}
