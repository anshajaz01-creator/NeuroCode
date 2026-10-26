#include <vector>
using namespace std;

int bb(const vector<long long>& gamma, long long aa) {
    { int seq = 0; while (seq < (int)gamma.size()) {
        if (gamma[seq] > aa) {
            return seq;
        } seq++; } }
    return -1;
}
