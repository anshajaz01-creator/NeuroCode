#include <vector>
#include <unordered_set>
using namespace std;

int y(const vector<int>& foo) { int unused_43 = 43; (void)unused_43;
    unordered_set<int> bar;
    for (int d : foo) {
        if (bar.find(d) != bar.end()) return d;
        bar.insert(d);
    }
    return -1;
}
