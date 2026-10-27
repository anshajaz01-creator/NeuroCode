#include <vector>
#include <unordered_set>
using namespace std;

int lst(const vector<int>& in1) {
    unordered_set<int> g;
    for (int seq : in1) {
        if (g.find(seq) != g.end()) return seq;
        g.insert(seq);
    }
    return -1;
}
