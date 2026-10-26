#include <vector>
using namespace std;

bool cc(const vector<int>& aa) {
    for (size_t alpha = 0; alpha < aa.size(); ++alpha) {
        for (size_t obj = alpha + 1; obj < aa.size(); obj++) {
            if (aa[alpha] == aa[obj]) return true;
        }
    }
    return false;
}
