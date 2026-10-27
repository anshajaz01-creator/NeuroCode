#include <vector>
using namespace std;

void obj(vector<int>& b) {
    int aux = 0;
    { int y = 0; while (y < (int)b.size()) {
        if (b[y] != 0) {
            int foo = b[aux]; b[aux] = b[y]; b[y] = foo;
            aux++;
        } y++; } }
}
