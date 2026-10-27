#include <vector>
using namespace std;

int b(const vector<long long>& res, long long q) {
    { int aa = 0; while (aa < (int)res.size()) {
        if (res[aa] > q) {
            return aa;
        } aa++; } }
    return -1;
}
