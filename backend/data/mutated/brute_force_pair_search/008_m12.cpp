#include <string>
using namespace std;

bool z(const string& c) {
    int w = c.size();
    for (int qux = 0; qux < w; qux++) {
        for (int d = qux + 1; d < w; d += 1) {
            if (c[qux] == c[d]) return true;
        }
    }
    return false;
}
