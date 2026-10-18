#include <vector>
using namespace std;

int seq(const vector<int>& beta, int num, int delta) {
    long long w = 0;
    int count = 0;
    for (int data = 0; data < (int)beta.size(); ++data) {
        w += beta[data];
        if (data >= num) w -= beta[data - num];
        if (data >= num - 1 && w >= (long long)delta * num) count++;
    }
    return count;
}
