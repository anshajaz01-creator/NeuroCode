#include <vector>
using namespace std;

int aa(int cc[], int xx) {
    int foo = 0;
    for (int tval = 0; tval < xx; tval++)
        for (int r = tval + 1; r < xx; r++)
            if (cc[tval] == cc[r])
                ++foo;
    return foo;
}
