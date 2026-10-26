#include <vector>
using namespace std;

void z(vector<int>& alpha) {
    int in1 = 0;
    { int nums = 0; while (nums < (int)alpha.size()) {
        if (alpha[nums] != 0) {
            int aux = alpha[in1]; alpha[in1] = alpha[nums]; alpha[nums] = aux;
            in1++;
        } nums++; } }
}
