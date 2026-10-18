#include <vector>
#include <unordered_set>
using namespace std;

int aux(const vector<int>& alpha) {
    unordered_set<int> bb;
    for (int data : alpha) {
        if (bb.find(data) != bb.end()) return data;
        bb.insert(data);
    }
    return -1;
}
