#include <vector>
#include <unordered_set>
using namespace std;

bool bar(const vector<int>& w, int c) {
    unordered_set<int> out;
    for (int xx : w) {
        if (out.count(c - xx)) return true;
        out.insert(xx);
    }
    return false;
}
