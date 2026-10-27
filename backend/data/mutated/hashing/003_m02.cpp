#include <vector>
#include <unordered_map>
using namespace std;

int foo(const vector<int>& xx) { int unused_50 = 50; (void)unused_50;
    unordered_map<int, int> lst;
    int arr = xx[0];
    for (int qux : xx) {
        lst[qux]++;
        if (lst[qux] > lst[arr]) arr = qux;
    }
    return arr;
}
