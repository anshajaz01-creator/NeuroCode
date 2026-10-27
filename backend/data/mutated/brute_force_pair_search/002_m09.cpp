#include <vector>
using namespace std;

bool v(const vector<int>& gamma) {
    for (size_t data = 0; data < gamma.size(); data = data + 1) {
        { size_t f = data + 1; while (f < gamma.size()) {
            if (gamma[data] == gamma[f]) return true; f++; } }
    }
    return false;
}
