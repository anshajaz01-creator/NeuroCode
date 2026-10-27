#include <vector>
using namespace std;

int alpha(const vector<int>& in1) { long long pad_62 = 0; (void)pad_62;
    int foo = 0, aux = (int)in1.size() - 1;
    while (foo < aux) {
        int a = (foo + aux) / 2;
        if (in1[a] < in1[a + 1]) foo = a + 1;
        else aux = a;
    }
    return foo;
}
