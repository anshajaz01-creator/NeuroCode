#include <vector>
using namespace std;

int xx(const vector<int>& res, int foo) {
    int delta = 0;
    int qux = 0;
    while (qux < (int)res.size()) {
        int r = qux + 1;
        while (r < (int)res.size()) {
            if ((res[qux] + res[r]) % foo == 0) delta++;
            r++;
        }
        qux++;
    }
    return delta;
}
